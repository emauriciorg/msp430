#include <msp430g2553.h>
#include"CDC.h"
#include <stdlimits.h>
#include <stdint.h>
volatile char rx_byte = 0;
volatile char side_t  = '0';
volatile unsigned int count[4];


void girar(char );

void uart_init()
{
	P1SEL |= ( BIT1|BIT2);
	P1SEL2 |= (BIT1| BIT2);
	UCA0CTL1 = UCSWRST;
	UCA0CTL1 |= UCSSEL_2;                     // SMCLK
	UCA0BR0 = 130;                            // 16MHz 9600 PREESCALAR
	UCA0BR1 = 6;                             //(UCAxBR0 + UCAxBR1 � 256)
	UCA0MCTL =6<<1;//UCBRS0;                        // Modulation UCBRSx = 1
	UCA0CTL1 &= ~UCSWRST;
	IE2 = UCA0RXIE;
}



void enable_timer(uint8_t on_off)
{
	if(on_off == true)
	{
		TA1CTL   = ID_3|TASSEL_2|MC_1; //UP mode
		TA1CCR0  = 40;
		TA1CCTL1 = OUTMOD_7| CCIE;
		TA1CCR1  = 000;
	}else
	{
 		TA1CTL   = 0;
		TA1CCR0  = 0;
		TA1CCTL1 = 0;
		TA1CCR1  = 0;

		P2SEL  &= ~(BIT1);
		P2SEL2 &= ~(BIT1);
		P2DIR  |= BIT1;
		P2OUT  &= ~BIT1;
	}
}


void enable_interrupts(void)
{
	_BIS_SR(GIE);
	__enable_interrupt();
	__bis_SR_register(GIE);
}


void clk_init()
{
	WDTCTL = WDTPW | WDTHOLD;                 // Stop WDT
	BCSCTL1 =CALBC1_16MHZ;
	BCSCTL2 =0;
	DCOCTL = CALDCO_16MHZ;
}


int main(void)
{
	clk_init();

	uart_init();

	P1SEL &= ~(BIT7|BIT6);
	P1SEL2&= ~(BIT7|BIT6);
	P1DIR |= (BIT7|BIT6);

	count[1] = 75;
	count[2] = 5000;
	count[0] = 0;

	enable_interrupts();
	enable_timer(true);

	uart_send_string("To modify PWM Press 'q' +=5 or 'a' -=5 ");

	while(1){
		print_uint(count[1]);
		line_jump();
	}
}



void girar(char SIDE_T )
{
	static uint8_t update_count = 0;
	if(update_count == 0)
	{
		update_count = 1;
		return;
	}
	update_count = 0;

	switch(SIDE_T)
	{
		case'R':if(count[1] < 92){ count[1]++; }break;
		case'L':if(count[1] > 65){ count[1]--; };break;
		case'Z':count[1] = 75; break;
	}
}


#pragma vector=USCIAB0RX_VECTOR
__interrupt void RXserial_isr(void)
{
	IFG2&=~UCA0RXIFG;

	rx_byte = UCA0RXBUF;

	switch(rx_byte)
	{
		case 'q':{	if(count[1] < 95){count[1]+=1;}	}break;
		case 'a':{	if(count[1] > 55){count[1]-=1;}	}break;
		case 'R':{	side_t='R';}	break;
		case 'L':{	side_t='L';}break;
		case 'Z':{	side_t='Z';}break;

	}

}


#pragma vector=TIMER1_A1_VECTOR
__interrupt void Timer1a1_isr(void)
{
	TA1CCTL1&=~CCIFG;
	//P1OUT^=BIT7;
	if(count[0] < count[1]) { P1OUT|=BIT7; }else{ P1OUT&=~BIT7; }
	if(count[0] < 1001) {count[0]++; } else{ count[0]=0; girar(side_t); }
}


#pragma vector=TIMER0_A0_VECTOR
__interrupt void Timer0a0_isr(void)
{
	P1OUT^=BIT6;
	TACCTL0&=~CCIFG;
}
