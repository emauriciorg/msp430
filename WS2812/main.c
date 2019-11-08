#include <msp430g2553.h>
#include"common/CDC.h"
#include "ws2813b.h"


#define LedPin BIT0
#define NUMBER_OF_LEDS 138
/************************************VARIABBLE AND MACROS******************************************************/
unsigned int Vin  = 1020;
unsigned int Vmax = 1020;
unsigned int VES1 = 510;
unsigned int VES2 = 612;
unsigned int VES3 = 795;
unsigned int Vout = 100;

char LedValue   = 0x80;
char LedRed;
char LedGreen;
char LedBlue;   = 0x40
char LedValueAux;
char LedNumber; = 0x08;

/*************************************FUNCTION DECLARATION******************************************************/
void clck_init(void);
void uart_init(void);
void interrupt_enable(void);


int main(void)
{

	volatile unsigned int i,j;
	clck_init();
	uart_init();
	interrupt_enable();

	DMACTL0=0;

	P2DIR  |= LedPin;
	P2SEL  &=~LedPin;
	P2SEL2 &=~LedPin;
	P2OUT  &=~LedPin;

	_delay_cycles(16000000);

	while(1)
	{

		for(j=0;j<=NUMBER_OF_LEDS;j++){
			for(i=0;i<=NUMBER_OF_LEDS;i++){

				//	ec("el numero de leds es");p_ui(NUMBER_OF_LEDS);p_ui(i);clc_();
				//		writeLed(LedRed,LedGreen,LedBlue);

				if((i) == (j-1)) {
					writeLed(LedRed,LedGreen,LedBlue);}
					else{
						writeLed(0,0,0);
					}
				}
				P2OUT&=~LedPin;
				_delay_cycles(500000);
			}

		/*
	 	 	writeLed(0x10,0x10,0x00);
			writeLed(0x00,0x00,0x00);
			writeLed(0x00,0x00,0x00);
			writeLed(0x00,0x00,0x00);
			writeLed(0x00,0x00,0x00);
			P2OUT=0;
			_delay_cycles(6000000);

				writeLed(0x10,0x10,0x00);
				writeLed(0x00,0x10,0x10);
				writeLed(0x00,0x00,0x00);
				writeLed(0x00,0x00,0x00);
				writeLed(0x00,0x00,0x00);

				P2OUT=0;
				_delay_cycles(6000000);

				writeLed(0x10,0x10,0x00);
				writeLed(0x00,0x10,0x10);
				writeLed(0x10,0x00,0x10);
				writeLed(0x00,0x00,0x00);
				writeLed(0x00,0x00,0x00);
				P2OUT=0;
				_delay_cycles(6000000);

				writeLed(0x10,0x10,0x00);
				writeLed(0x00,0x10,0x10);
				writeLed(0x10,0x00,0x10);
				writeLed(0x10,0x00,0x00);
				writeLed(0x00,0x00,0x00);
				P2OUT=0;
				_delay_cycles(6000000);

				  writeLed(0x10,0x10,0x00);
				  writeLed(0x00,0x10,0x10);
				  writeLed(0x10,0x00,0x10);
				  writeLed(0x10,0x00,0x00);
				  writeLed(0x00,0x00,0x10);
				  P2OUT=0;
				  _delay_cycles(6000000);

				  writeLed(0x00,0x00,0x00);
				  writeLed(0x00,0x00,0x00);
 			writeLed(0x00,0x00,0x00);
				 writeLed(0x00,0x00,0x00);
				 writeLed(0x00,0x00,0x00);
				 P2OUT=0;
				 _delay_cycles(6000000);

*/

		}
	}


/***********************************END OF MAIN RUTINE**************************************************/




void uart_init()
{
				P1SEL |= ( BIT1|BIT2);
				P1SEL2 |= (BIT1| BIT2);
				UCA0CTL1 = UCSWRST;
				UCA0CTL1 |= UCSSEL_2;                     // SMCLK
				UCA0BR0 = 130;//65;                            // 16MHz 9600 PREESCALAR
				UCA0BR1 = 6;//3;                             //(UCAxBR0 + UCAxBR1 � 256)
				UCA0MCTL =6<<1;//UCBRS0;                        // Modulation UCBRSx = 1
				UCA0CTL1 &= ~UCSWRST;
				IE2 = UCA0RXIE;
}


void interrupt_enable(void)
{
	_BIS_SR(GIE);
	__enable_interrupt();
	__bis_SR_register(GIE);
}

void clck_init(void)
{
			WDTCTL = WDTPW | WDTHOLD;
			BCSCTL1 =CALBC1_16MHZ;
			BCSCTL2 =0;
			DCOCTL = CALDCO_16MHZ;
}


/*************************************INTERRUPT*******************************************/

#pragma vector=USCIAB0RX_VECTOR
__interrupt void RXserial_isr(void)
{
	IFG2&=~UCA0RXIFG;
	LedValueAux = LedValue-'0';
	LedValue = UCA0RXBUF;

	if(LedValue==('s'-'0')){
		LedRed   = LedBlue;
		LedBlue  = LedGreen;
		LedGreen = LedValueAux*100;
	}

	switch(LedValue) {
	case 'r': LedRed    = LedValueAux*20; break;
	case 'g': LedGreen  = LedValueAux*20; break;
	case 'b': LedBlue   = LedValueAux*20; break;
	case 'L': LedNumber = LedValue;       break;
	}
}
