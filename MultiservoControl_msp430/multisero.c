#include <msp430.h> 
#include"CDC.h"
/*
 * main.c
 */

#define ServoOne BIT0
#define ServoTwo BIT1

#define OServoOne BIT2
#define OServoTwo BIT3


#define ServoOne1 BIT4
#define ServoTwo2 BIT5

#define OServoOne1 BIT6
#define OServoTwo2 BIT7


#define LeftArmjoint1 BIT0
#define LeftArmjoint2 BIT1
#define LeftLegjoint1 BIT2
#define LeftLegjoint2 BIT3

#define RightArmjoint1 BIT4
#define RightArmjoint2 BIT5
#define RightLegjoint1 BIT6
#define RightLegjoint2 BIT7



volatile unsigned int an1=80,an2=40;
volatile unsigned int an3=200,an4=40,an5=80,an6=40,an7=80,an8=40,countt,DES,G_IRA;


/*Patrones de caminata basados en el mapeo de angulos*/

char Rjoint1[6]={80,   80, 103, 103,   80, 80};
char Rjoint2[6]={40,   30,  30,  50,   50, 40};

char RLjoint1[6]={80,   80, 103, 103,   80, 80};
char RLjoint2[6]={40,   30,  30,  50,   50, 40};


char LRjoint1[6]={80,   80,  57,  57,   80, 80};
char LRjoint2[6]={40,   50,  50,  30,   30, 40};

char LLjoint1[6]={80,   80,  57,  57,   80, 80};
char LLjoint2[6]={40,   50,  50,  30,   30, 40};

void legpattern();


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
void Enin();

	/*Funcion para manipular 8 servos*/

    void servo(int ser1,int ser2, int ser3, int ser4, int ser5, int ser6, int ser7, int ser8  )
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

		if(countt<ser3){P2OUT|=OServoOne;}else{P2OUT&=~OServoOne;}//SERVO3
		if(countt<ser4){P2OUT|=OServoTwo;}else{P2OUT&=~OServoTwo;}//SERVO4

		if(countt<ser5){P2OUT|=ServoOne1;}else{P2OUT&=~ServoOne1;}//SERVO4
		if(countt<ser6){P2OUT|=ServoTwo2;}else{P2OUT&=~ServoTwo2;}//SERVO4

		if(countt<ser7){P2OUT|=OServoOne1;}else{P2OUT&=~OServoOne1;}//SERVO4
		if(countt<ser8){P2OUT|=OServoTwo2;}else{P2OUT&=~OServoTwo2;}//SERVO4

		//76
		if(countt<1001){countt++;}else{countt=0;SerOK++;}


	 }while(SerOK!=10);
   	   countt=0;
		TACCTL0|=TACLR;
		G_IRA=0;
		SerOK=0;
  }
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

    void clk()
			{
				WDTCTL = WDTPW | WDTHOLD;
				BCSCTL1 =CALBC1_16MHZ;
				BCSCTL2 =0;
				DCOCTL = CALDCO_16MHZ;
			}
    void uart();
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
		clk();
		uart();
		Enin();
		/*Habilita los pines que controlan los servos*/
		P2SEL2&=~(OServoOne|OServoTwo|ServoOne|ServoTwo|OServoOne1|OServoTwo2|ServoOne1|ServoTwo2);
		P2SEL&= ~(OServoOne|OServoTwo|ServoOne|ServoTwo|OServoOne1|OServoTwo2|ServoOne1|ServoTwo2);
		P2DIR|=  (OServoOne|OServoTwo|ServoOne|ServoTwo|OServoOne1|OServoTwo2|ServoOne1|ServoTwo2);
		P2OUT&= ~(OServoOne|OServoTwo|ServoOne|ServoTwo|OServoOne1|OServoTwo2|ServoOne1|ServoTwo2);

		while(1)
		{

		legpattern();
	    //for(icount=20;icount<=5000;icount+=10)
	    //{
	   //for(itimes=0;itimes<=4;itimes++){
	    //	DelaySecond(icount);
	    //an1=111;an2=111;
	   // ec("servos:");PrintUInt(an1);s_pc();PrintUInt(an2);s_pc();PrintUInt(an3);clc_();
		//TwoServo(an1,an2);
		//DelaySecond(icount);
	    //an1=50;an2=28;
	    //TwoServo(an1,an2);
	    //	ec("servos:");PrintUInt(an1);s_pc();PrintUInt(an2);s_pc();PrintUInt(an3);s_pc();PrintUInt(an4);clc_();
	    //ec("servos:");PrintUInt(an1);s_pc();PrintUInt(an2);s_pc();PrintUInt(an3);clc_();
	  // }

	    }
	//	}
	
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

		void legpattern()
		{
			volatile char k =0;
			for(k=0;k<=5;k++)
			{
					/*extremidades de la izquierda*/
				an1=Rjoint1[k];
				an2=Rjoint2[k];
				an3=LRjoint1[k];
				an4=LRjoint2[k];
					/*Extremidades de la derecha*/
				an5=Rjoint1[k];
				an6=Rjoint2[k];
				an7=LRjoint1[k];
				an8=LRjoint2[k];

				servo(an1,an2,an3,an4,an5,an6,an7,an8);

				ec("servos:");PrintUInt(an1);s_pc();PrintUInt(an2);s_pc();PrintUInt(an3);s_pc();PrintUInt(an4);clc_();

				_delay_cycles(8000000);
			}


		}

		/*ajuste de angulo mediante comunicacion serial*/
#pragma vector=USCIAB0RX_VECTOR
__interrupt void RXserial_isr(void)
{
	IFG2&=~UCA0RXIFG;
	DES=UCA0RXBUF;
	switch(DES)
	{
		case 'q':{	if(an1<995){an1+=1;}	}break;
		case 'a':{	if(an1>4){an1-=1;}	}break;

		case 'w':{	if(an2<995){an2+=1;}	}break;
		case 's':{	if(an2>4){an2-=1;}	}break;

		case 'e':{an3+=1;	}break;
		case 'd':{	if(an3>2){an3-=1;}	}break;

	}
}
