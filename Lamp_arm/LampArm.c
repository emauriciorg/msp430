#include <msp430.h> 
#include"CDC.h"
/*
 * main.c
 */

#define ServoOne BIT0
#define ServoTwo BIT1
#define LEDLight BIT2



volatile unsigned int an1=80,an2=40,an3=500;
volatile unsigned int countt,DES,G_IRA;


/*Patrones de caminata basados en el mapeo de angulos*/

char SequenceServoOne[6]={80,   80, 103, 103,   80, 80};
char SequenceServoTwo[6]={40,   30,  30,  50,   50, 40};

void WhiteLed();



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
			TACTL|=TACLR;
			SerOK=0;
		}
void enable_interrupts();

	/*Funcion para manipular 8 servos*/


    void TwoServo(int ser1,int ser2)
   	{
       volatile int SerOK=0;

       TACTL	 = ID_3|TASSEL_2|MC_1; //UP mode
   	   TACCR0	 = 40;//20us
   	   TACCTL0 =OUTMOD_7;
   	   TACCR1=0;

   	 do{

   		while((TACCTL0&CCIFG)!=CCIFG);

   		TACCTL0&=~CCIFG;

   		if(countt<ser1){P2OUT|=ServoOne;}else{P2OUT&=~ServoOne;}//SERVO1
   		if(countt<ser2){P2OUT|=ServoTwo;}else{P2OUT&=~ServoTwo;}//SERVO2
   		if(countt<1001){countt++;}else{countt=0;SerOK++;}


   	 }while(SerOK!=10);
      	   countt=0;
   		TACCTL0|=TACLR;
   		SerOK=0;
     }




    void clk_init()
			{
				WDTCTL = WDTPW | WDTHOLD;
				BCSCTL1 =CALBC1_16MHZ;
				BCSCTL2 =0;
				DCOCTL = CALDCO_16MHZ;
			}
    void uart_init();
void DelaySecond(int Second)
{
	volatile int CounterS;
	for(CounterS=0;CounterS<Second;CounterS++)
	{
	   _delay_cycles(16000); //16 000
    }

}


    int main(void)
	{
volatile int icount=20,itimes=0;
		clk_init();
		uart_init();
		enable_interrupts();
		/*Habilita los pines que controlan los servos*/
		P2SEL2&=~(LEDLight|ServoOne|ServoTwo);
		//P2SEL&= ~(LEDLight|ServoOne|ServoTwo);
		P2DIR|=  (LEDLight|ServoOne|ServoTwo);

		P2SEL|= (LEDLight|ServoOne|ServoTwo);
		P2OUT&= ~(LEDLight|ServoOne|ServoTwo);

		WhiteLed();

		while(1)
		{

		//legpattern();

	    uart_send_string("servos:");PrintUInt(an1);s_pc();PrintUInt(TA1CCR0);s_pc();PrintUInt(TA1CCR1);clc_();
		//TwoServo(an1,an2);

	    }
	

	}


    void WhiteLed()
       	{


           TA1CCR0	 = 1000;//20us
       	   TA1CCTL1 =OUTMOD_7;
       	   TA1CCR1	 = 500;//20us
       	   TA1CTL	 = ID_3|TASSEL_2|MC_1; //UP mode

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


		/*ajuste de angulo mediante comunicacion serial*/
#pragma vector=USCIAB0RX_VECTOR
__interrupt void RXserial_isr(void)
{
	IFG2&=~UCA0RXIFG;
	DES=UCA0RXBUF;
	switch(DES)
	{


		case 'e':{TA1CCR1+=10;	}break;
		case 'd':{	TA1CCR1-=10;}	break;

	}
}
