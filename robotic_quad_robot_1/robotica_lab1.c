#include <msp430.h> 
#include"CDC.h"
/*
 * main.c
 */
#define  M12	BIT0
#define	 M11	BIT1
#define	 EN_T	BIT2
#define  M21	BIT3
#define  M22    BIT4

volatile unsigned int an1=76,an2=76,an3=76,countt,DES,G_IRA;
int automa=0;
char dirR='N';
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
			 countt=0;
			TACCTL0|=TACLR;
			SerOK=0;
		}
void enable_interrupts();



	void TurnLeft()
	{
		P2OUT=EN_T|M11|M22;  //MOVE M1 FORWARD , M2 BACKWARDS

	}

void TurnRight()
{
	P2OUT=EN_T|M12|M21;  //MOVE M2 FORWARD , M1 BACKWARDS

}

void Turnoff()
{
	P2OUT=0;
}


void Backwards()
{

	P2OUT=EN_T|M12|M22;  //MOVE M2 FORWARD , M1 BACKWARDS

}

void Forwards()
{

	P2OUT=EN_T|M11|M21;  //MOVE M2 FORWARD , M1 BACKWARDS
}

void Stop_bot()
{

	P2OUT=0;  //MOVE M2 FORWARD , M1 BACKWARDS
}

void nobrain()
{

	P2OUT=EN_T|M11|M21;  //MOVE M1 AND M2 FORWARD


}

void clk_init()
			{
				WDTCTL = WDTPW | WDTHOLD;
				BCSCTL1 =CALBC1_16MHZ;
				BCSCTL2 =0;
				DCOCTL = CALDCO_16MHZ;
			}
void uart_init();
	int main(void)
	{

		clk_init();
		uart_init();
		enable_interrupts();
		P2SEL2&=~(0xff);
		P2SEL&=~(0xff);
		P2DIR|=(EN_T|M11|M12|M21|M22);
		P2OUT&=~(0xff);

		while(1)
		{


		//servo(an1,an2,an3);
		uart_write_byte(dirR);uart_write_byte('X');clc_();
		/*    FUNCION AI BASIC
			if(automa==1)
			{
				Forwards();
			P2OUT=0;
			} */
		}
	
	}



	   void enable_interrupts()
	 		{
	 			_BIS_SR(GIE);
	 			__enable_interrupt();
	 			__bis_SR_register(GIE);
	 		}
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


#pragma vector=USCIAB0RX_VECTOR
__interrupt void RXserial_isr(void)
{
	IFG2&=~UCA0RXIFG;
	DES=UCA0RXBUF;
	switch(DES)
	{
		case 'W':{Forwards();dirR='F';	}break;
		case 'S':{	Backwards();dirR='B';	}break;

		case 'A':{TurnLeft();dirR='L';	}break;
		case 'D':{TurnRight();dirR='R';	}break;

		case 'Q':{dirR='A';};break;//auto
		case 'E':{dirR='0';Stop_bot();};break;
		default:{dirR=dirR;}break;
	}
}
