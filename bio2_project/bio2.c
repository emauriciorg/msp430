#include <msp430g2553.h>
#include <stdint.h>
#include"CDC.h"


volatile uint16_t voice[9];
volatile uint16_t temp;

void uart_init(void)
{
	P1SEL    |= ( BIT1 | BIT2);
	P1SEL2   |= ( BIT1 | BIT2);
	UCA0CTL1  = UCSWRST;
	UCA0CTL1 |= 0x80;               // SMCLK
/*	UCA0BR0 = 138;                            // 16MHz 9600 PREESCALAR
	UCA0BR1 = 0;                             //(UCAxBR0 + UCAxBR1 � 256)
	UCA0MCTL =0x0E;//UCBRS0;                        // Modulation UCBRSx = 1
*/
	UCA0BR0   = 130;                   // 16MHz 9600 PREESCALAR
	UCA0MCTL  = 0x0C;                  // Modulation UCBRSx = 1
	UCA0CTL1 &= ~UCSWRST;
	IE2      &=~ UCA0RXIE| UCA0TXIE; /*TX&RX interrupt enabled */
}


void timer_init(void)
{

	TA1CTL	 = ID_1|TASSEL_2|MC_1; //UP mode
	TA1CCR0	 = 500;
	TA1CCTL1 =OUTMOD_7| CCIE;
	TA1CCR1=100;


	P2SEL&=~(BIT0|BIT1);
	P2SEL|=(BIT2|BIT1);

	P2SEL2&=~(BIT0 |BIT1);
	P2DIR|=BIT0|BIT1;

}


void ADC10_init()
{
	ADC10CTL1 = INCH_5 | ADC10DIV_7 | CONSEQ_2 ;     // CHANEL INPUT AND MODE
	ADC10CTL0 = ADC10SHT_3 | ADC10SR |REFBURST | MSC | REF2_5V | REFON | ADC10ON | ADC10IE;  // REFERENCE AND TIMING
	ADC10AE0 |= BIT5;//ENABLE THE ANALOG CHANNEL ADC option
}


void enable_interrutps(void)
{
	_BIS_SR(GIE);
	__enable_interrupt();
	__bis_SR_register(GIE);
}


void clk_init(void)
{
	WDTCTL  = WDTPW | WDTHOLD;   // Stop WDT
	BCSCTL1 = CALBC1_16MHZ;
	BCSCTL2 = 0x00;
	DCOCTL  = CALDCO_16MHZ;
}


void ADC10_enable()
{
	ADC10CTL0 |= (ENC|ADC10SC ) ;
}

int main(void)
{
	clk_init();
	ADC10_init();
	uart_init();

	enable_interrutps();
	ADC10_enable();

	while(1)
	{
		voice[6] = voice[5]/4;
		uart_write(voice[6]);
		if( temp2 >= 127) {
			temp2=0;
			_delay_cycles(500000);
		}else{
			temp2++;
		}
		_delay_cycles(32000);
	};

}


#pragma vector=ADC10_VECTOR
__interrupt void ADC10_in()
{
	ADC10CTL0 &=~ ADC10IFG;

	voice[4] = voice[3];
	voice[3] = voice[2];
	voice[2] = voice[1];
	voice[1] = voice[0];
	voice[0] = ADC10MEM;

	voice[5]=(voice[0]
		+ voice[1]
		+ voice[2]
		+ voice[3]
		+ voice[4])/5;

}


#pragma vector=TIMER1_A1_VECTOR
__interrupt void Timer1a1_isr(void)
{
	TA1CCR1=voice;
	TA1CCTL1&=~CCIFG;
}
