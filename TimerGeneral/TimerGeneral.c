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
	}

   void Timer_block();

	int main(void)
	{
		clk();
uart();
      Timer_block();


	}
	const unsigned short seno[20] =
	{
	      127,	146, 	163, 177, 	185,
	      189, 	185,	177, 163, 	146,
	      127, 	107,	 90,  76, 	68,
	      65 ,  68 ,  	 76,  90,   107
	};


	/*

		const unsigned short seno[20]= //Matlab_sine
		{
				35,	46,	56,	64,	69,
				70,	67,	61,	52,	41,
				29,	18,	9,	3, 0,
				1,	6,	14,	24,	35
		};

*/
			   void Timer_block()
	   {

		   TA1CTL=TASSEL_2|MC_1|TAIE;
		   TA1CCR0=Nmax;
		   TA1CCTL1=OUTMOD_7;

		   TA1CCR1=seno[0];


		   P2SEL&=~(BIT0|BIT1);
		   P2SEL|=(BIT2|BIT1);

		   P2SEL2&=~(BIT0 |BIT1);
		   //P2SEL|=BIT2;
		   P2DIR|=BIT0|BIT1;

		   /*ENABLE INTERRUPT*/

		   			_BIS_SR(GIE);
		   			__enable_interrupt();
		   			__bis_SR_register(GIE);





	   }

#pragma vector=USCIAB0RX_VECTOR
	__interrupt void RXserial_isr(void)
	{
		IFG2&=~UCA0RXIFG;
		datain=UCA0RXBUF;
					if(datain=='w')
					{  isum=1;
					  voltaux=voltaux+isum;
					}
					else{isum=-1; voltaux=voltaux+isum;}
					if(voltaux>Nmax){voltaux=voltaux-isum; }
					volt=voltaux;
	}

#pragma vector=TIMER1_A1_VECTOR
	__interrupt void Timer0a1_isr(void)
	{

		   TA1CTL&=~TAIFG;
	TA1CCTL0&=~CCIFG;


	TA1CCR1=volt;//seno[i_n]+10;


		//if(i_n<19){i_n++;}else{i_n=0;}

	}


