#include <msp430.h> 
#include"CDC.h"
/*
 * main.c
 */

volatile unsigned int an1=76,an2=35,an3=103,countt,DES,G_IRA;

char joint2[6]={103,103,118,118,103,103};
char joint1[6]={50, 36, 36, 66,66,50};


void Enin();


	void Timer_module(int dutycycle)
	{
		volatile int SerOK=0;
		P1DIR|=BIT6;
		P1SEL|=BIT6;
		P1SEL2&=~(BIT6);

 	   TACTL	 = ID_3|TASSEL_2|MC_1;
	   TACCR0	 = 500;// Fijo para la frecuencia
	   TACCTL1 =OUTMOD_7;
	   TACCR1=50; //variable
	}

void clk()
			{
				WDTCTL = WDTPW | WDTHOLD;
				BCSCTL1 =CALBC1_16MHZ;
				BCSCTL2 =0;
				DCOCTL = CALDCO_16MHZ;
			}
void uart();
	int main(void)
	{

		clk();
		uart();
		Enin();
		Timer_module(100);
		while(1)
		{

					ec("sending pwm:");p_ui(TACCR1);clc_();




		}
	
	}



	   void Enin()
	 		{
	 			_BIS_SR(GIE);
	 			__enable_interrupt();
	 			__bis_SR_register(GIE);
	 		}
	  void uart()
		   {
				P1SEL |= ( BIT1|BIT2);
				P1SEL2 |= (BIT1| BIT2);
				UCA0CTL1 = UCSWRST;
				UCA0CTL1 |= UCSSEL_2;                     // SMCLK
				UCA0BR0 = 130;//65;                            // 16MHz 9600 PREESCALAR
				UCA0BR1 = 6;//3;                             //(UCAxBR0 + UCAxBR1 × 256)
				UCA0MCTL =6<<1;//UCBRS0;                        // Modulation UCBRSx = 1
				UCA0CTL1 &= ~UCSWRST;
				IE2 = UCA0RXIE;
		   }

#pragma vector=USCIAB0RX_VECTOR
__interrupt void RXserial_isr(void)
{
	IFG2&=~UCA0RXIFG;
	DES=UCA0RXBUF;
	switch(DES)
	{
		case 'a':{	if(an1<490){TACCR1+=2;}	}break;
		case 's':{	if(an1>4){TACCR1-=2;}	}break;


	}
}
/*#pragma vector=TIMER0_A0_VECTOR
__interrupt void Timer0A0_ISR(void)
{
	TACCTL0&=~CCIFG;
}
*/
