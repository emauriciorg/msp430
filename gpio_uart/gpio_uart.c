#include <msp430.h> 
#include"CDC.h"
/*
 * main.c
 */

volatile unsigned int an1=76,an2=76,an3=76,countt,DES,G_IRA;
void delay_millis(int millis)
{
	 volatile int times,SerOK=0,countt=0;
		times=500*millis;


 	   TACTL	 = ID_3|TASSEL_2|MC_1; //UP mode
	   TACCR0	 = 4; //each 2us
	   TACCTL0 =OUTMOD_7;
	   TACCR1=0;


	    do{

	    	while((TACCTL0&CCIFG)!=CCIFG);
			TACCTL0&=~CCIFG;

			if(countt<times){countt++;}
			else{
						 SerOK=10;
			    }
	    }while(SerOK!=10); //number of times of the count
		TACCTL0|=TACLR;

}

	void delay_seconds(int tx)
	{

		 volatile int times,SerOK=0,countt=0;
			times=50*tx;

			TACTL	 = ID_3|TASSEL_2|MC_1; //UP mode
			TACCR0	 = 40000; //each 0.02us
			TACCTL0 =OUTMOD_7;
			TACCR1=0;

			 do{

				while((TACCTL0&CCIFG)!=CCIFG);
				TACCTL0&=~CCIFG;

					if(countt<times){countt++;}
					else{
								 SerOK=10;
						}
			 }while(SerOK!=10); //number of times of the count
			TACCTL0|=TACLR;

		}
void Enin();


	void servo(int ser1,int ser2, int ser3){
volatile int SerOK=0;


 	   TACTL	 = ID_3|TASSEL_2|MC_1; //UP mode
	   TACCR0	 = 40;//20us
	   TACCTL0 =OUTMOD_7;
	   TACCR1=0;

	 do{

		while((TACCTL0&CCIFG)!=CCIFG);

		TACCTL0&=~CCIFG;

		if(countt<ser1){P2OUT|=BIT0;}else{P2OUT&=~BIT0;}//SERVO1
		if(countt<ser2){P2OUT|=BIT1;}else{P2OUT&=~BIT1;}//SERVO2 25 118
		if(countt<ser3){P2OUT|=BIT2;}else{P2OUT&=~BIT2;}//SERVO3
//76
		if(countt<1001){countt++;}else{countt=0;SerOK++;}



	 }while(SerOK!=10);
   	   countt=0;
		TACCTL0|=TACLR;
		G_IRA=0;
		SerOK=0;


}

	void requestS()
	{

		//P1DIR|=(BIT0);
		P1OUT|=BIT0;
		delay_millis(14);
		P1OUT&=~BIT0;
		delay_millis(14);
		//P1DIR&=~(BIT0);
		P1OUT|=BIT0;


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




		P1SEL2&=~(BIT0);
		P1SEL&=~(BIT0);
		P1DIR|=(BIT0);
		P1OUT|=(BIT0);




		while(1)
		{


		ec("Press a key :");p_ui();

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

		if(DES== 'a'){	requestS();	}

}
