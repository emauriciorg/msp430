#include <msp430.h> 
#include"ConfigInicial.h"
#include"conversordatos.h"

#define XAxis BIT0
#define YAxis BIT1
#define LedGreen BIT6
#define KPeriod      10
#define KFrequency   10000




unsigned int Count=0,CountT1=0, CountX=0,CountX1=0,CountY=0,CountY1=0;
char StopTimer=0,StopTimer2=0;
unsigned char showX=1;
void Timer1En()
{
//TA1CCR0=9999;
  TA1CCR0=1999;
  TA1CCTL1=OUTMOD_7; //no capture mode+CCIA+Asynchronous en capture mode+modo comparacion+
  TA1CTL=TASSEL_2|ID_3|MC_1|TAIE;
}



int main(void)
{

    	configclk();
		ConfUart();

	 	 P1DIR|=(LedGreen);
	 	 P1SEL&=~(LedGreen);
	 	 P1SEL2&=~(LedGreen);
	 	 P1OUT&=~(LedGreen);

	 	 P1DIR&=~XAxis;
	 	 P1SEL&=~XAxis;
	 	 P1SEL2&=~XAxis;
	 	 P1IE|=XAxis;
	 	 P1IES|=XAxis;

	 	Timer1En();
		EnableInterrupts();

	 while(1)
	 {


	/*	 if(CountX*0.05>50)
		 {
			 StopTimer='1';
		 }
		 switch(StopTimer)
		 {
		 case '0': {
		*/		    /*PrintString(" rpm ");print_uint((20000/CountX1)*6);*/
			if(CountX1!=0){
		 PrintString(" Frecuencia ");print_uint((KFrequency/CountX1)*10);PrintString(" mHz ");PrintString("Tiempo ");print_uint(CountX1*KPeriod);PrintString(" mS ");line_jump();
			}//PrintString("Tiempo ");print_uint(CountX*50);PrintString(" mS");PrintString(" Frecuencia ");print_uint(20000/CountX);PrintString(" mHz");line_jump();
		/*	 	   }break;
		 case '1': {
			       PrintString("No detectado                                                                                           ");line_jump();TA1CCR0=0;
			       }break;
		 }
*/



	 }
}



#pragma vector=USCIAB0RX_VECTOR
__interrupt void  receiver(void){

	IFG2&=~UCA0RXIFG;
}


#pragma vector=PORT1_VECTOR
__interrupt void port1(void)
{


	if(P1IFG&XAxis)
	{
		//StopTimer='0';
		//Timer1En();
		CountX1=CountX;
		CountX&=0;
		Count&=0;
	//	P1OUT^=LedGreen;
	}/*else
	{

		StopTimer2='0';
		Timer0En();
		CountY1=CountY;
		CountY=0;
		CountT1=0;//  this counter could be similar?



	}
*/
	P1IFG=0x00;
}



#pragma vector=TIMER1_A1_VECTOR
__interrupt void EjeX_Timer(void){

//	if(TA1CTL&TAIFG)
	//{
	 TA1CTL&=~TAIFG;
	 if(Count>8){Count&=0;CountX++;}else{Count++;}

//	}
}
