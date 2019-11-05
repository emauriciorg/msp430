#include <msp430.h> 
#include"ConfigInicial.h"
#include"conversordatos.h"

#define XAxis BIT0
#define YAxis BIT1
#define LedGreen BIT6
#define KPeriod      10
#define KFrequency   10000
#define TaccrValue   1999



unsigned int CountTimerX=0,CountX=0,CountX1=0;
unsigned int CountTimerY=0,CountY=0,CountY1=0;
char StopTimer=0,StopTimer2=0;
unsigned char showX=1;
unsigned char IsXAxis=0,IsYAxis=0;
void Timer1En()
{
//TA1CCR0=9999;
  TA1CCR0=TaccrValue;
  TA1CCTL1=OUTMOD_7; //no capture mode+CCIA+Asynchronous en capture mode+modo comparacion+
  TA1CTL=TASSEL_2|ID_3|MC_1|TAIE;
}

/*void Timer0En()
{
//TA1CCR0=9999;
  TACCR0=TaccrValue;
  TACCTL1=OUTMOD_7; //no capture mode+CCIA+Asynchronous en capture mode+modo comparacion+
  TACTL=TASSEL_2|ID_3|MC_1|TAIE;
}
*/
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
		if(CountX1!=0)
		{
			PrintString("X");printuint((KFrequency/CountX1)*10);PrintString(" mHz ");PrintString("T ");printuint(CountX1*KPeriod);PrintString(" mS ");borrar();
		}
		if(CountX1!=0)
		{
			PrintString("Y");printuint((KFrequency/CountX1)*10);PrintString(" mHz ");PrintString("T");printuint(CountX1*KPeriod);PrintString(" mS ");borrar();
		}
	 }
}


#pragma vector=USCIAB0RX_VECTOR
__interrupt void  receiver(void)
{
	IFG2&=~UCA0RXIFG;
}


#pragma vector=PORT1_VECTOR
__interrupt void port1(void)
{
	if(P1IFG&XAxis)
	{
		//StopTimer='0';
		CountX1=CountX;
		CountX&=0;
		CountTimerX&=0;
	//	P1OUT^=LedGreen;
	}else
	{
	//	StopTimer2='0';
		CountY1=CountX;
		CountY&=0;
		CountTimerY&=0;
	}
	P1IFG=0x00;
}



#pragma vector=TIMER1_A1_VECTOR
__interrupt void EjeX_Timer(void)
{

	 TA1CTL&=~TAIFG;
	 if(CountTimerX>8){CountTimerX&=0;CountX++;}else{CountTimerX++;}
	 if(CountTimerY>8){CountTimerY&=0;CountY++;}else{CountTimerY++;}

}
