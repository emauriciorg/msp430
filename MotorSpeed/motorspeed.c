#include <msp430.h> 
#include"CDC.h"
/*
 * main.c
 */

#define ServoOne BIT0
#define ServoTwo BIT1



volatile unsigned int an1=80,an2=40;
volatile unsigned int an3=200,an4=40,an5=80,an6=40,an7=80,an8=40,countt,DES,G_IRA;


/*Patrones de caminata basados en el mapeo de angulos*/

void uart_init();


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
			G_IRA=0;
			SerOK=0;
		 }



    void clk_init()
	{
		WDTCTL = WDTPW | WDTHOLD;
		BCSCTL1 =CALBC1_16MHZ;
		BCSCTL2 =0;
		DCOCTL = CALDCO_16MHZ;
	}



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
		P2SEL2&=~(ServoOne|ServoTwo);
		P2SEL&= ~(ServoOne|ServoTwo);
		P2DIR|=  (ServoOne|ServoTwo);
		P2OUT&= ~(ServoOne|ServoTwo);

		while(1)
		{

		TwoServo(an1,an2);
	    uart_send_string("motor1:");PrintUInt(an1);uart_send_string(" motor2 :");PrintUInt(an2);clc_();
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


		/*ajuste de angulo mediante comunicacion serial*/
#pragma vector=USCIAB0RX_VECTOR
__interrupt void RXserial_isr(void)
{
	IFG2&=~UCA0RXIFG;
	DES=UCA0RXBUF;
	switch(DES)
	{
		case 'q':{	an1+=1;	}break;
		case 'a':{	an1-=1;	}break;

		case 'w':{  an2+=1;	}break;
		case 's':{	an2-=1;	}break;
		case '0':{	an2=0;an1=0;	}break;
		case '1':{	an2=250;an1=250;	}break;
		case '2':{	an2=750 ;an1=500;	}break;
    //	case 'e':{an3+=1;	}break;
	//	case 'd':{	if(an3>2){an3-=1;}	}break;

	}
}
