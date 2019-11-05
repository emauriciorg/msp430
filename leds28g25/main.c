#include <msp430.h>

/*
 * TimerGeneral.c
 *
 *Author: Mauricio Rios
 */

#define Nmax 150
unsigned char datain='0';
unsigned int volt=0,voltaux=0;
int isum=0;
	volatile unsigned char i_n=0;

	void uart()
	{
		P1SEL |= ( BIT1|BIT2);
		P1SEL2 |= ( BIT1|BIT2);
		UCA0CTL1 = UCSWRST;
		UCA0CTL1 |= 0x80;                     // SMCLK
		UCA0BR0 = 130;                            // 16MHz 9600 PREESCALAR
		UCA0BR1 = 6;                             //(UCAxBR0 + UCAxBR1 × 256)
		UCA0MCTL =0x0c;//UCBRS0;                        // Modulation UCBRSx = 1
		UCA0CTL1 &= ~UCSWRST;
		IE2 |= UCA0RXIE;
	}
	void clk()
	{
		WDTCTL = WDTPW | WDTHOLD;

		BCSCTL1 =CALBC1_16MHZ;
		BCSCTL2 =0x00;
		DCOCTL = CALDCO_16MHZ;
	    P2SEL=0;
	    P2SEL2=0;
	    P2DIR|=BIT6;
	}


	int main(void)
	{
		clk();

   while(1)
   {
	   _delay_cycles(10000000);
	   P2OUT^=BIT6;

   }

	}
