#include <msp430g2553.h>
//#include"CDC.h"
#include"FBF.h"
#include"lcd16x2.h"
#include"Timer.h"
#include"DefConf.h"


unsigned int CountTempY=0,CountTempX=0;
 unsigned int CountTempXS=0;
 unsigned int CountX=0;
 unsigned int CountTempXX[5];
volatile unsigned int CountX1=0;
char SampleCounter=0;
volatile unsigned int CountY=0;
volatile unsigned int CountY1=0;
volatile unsigned int CountTime=0;
volatile unsigned char CountIFG=1;
volatile unsigned char SampleYIFG=0,SampleXIFG=0;

int main(void)
{
clk();

/***Setup of LCD********/

P1DIR&=~(XAxis|YAxis);
P1SEL&=~(XAxis|YAxis);
P1SEL2&=~(XAxis|YAxis);
P1IE|=(XAxis);
P1IES|=(XAxis|YAxis);
P1OUT=0;
P1IFG=0;

P1DIR|=GreenLed;
P1SEL&=~GreenLed;
P1SEL2&=~GreenLed;


//	P1IES=0X08;
//  0 MEANS low-to-high transition, 1 means a high-to-low transition



LcdInicio();
P2SEL2=0X00;
P2SEL=0X00;
P2DIR=0XFF;
P2OUT=0;

ClearDisplay();
SetCursorPosition(0, 0);
PrintStr("Cargando...");//LPrintUInt(0);/*PrintString(" mHz ");*/
_delay_cycles(16000000);

SetCursorPosition(0, 0);
PrintStr("Fx ");
SetCursorPosition(0, 8);
PrintStr(" mHz");

SetCursorPosition(2, 0);
PrintStr("Fy ");
SetCursorPosition(2, 8);
PrintStr(" mHz");

Timer1En();
Enin();
 while(1)
 {

	   while(CountIFG)
	   {

		if(SampleCounter<5) //modified
		   {
			CountTempX=(1000000/(CountX1*2));if(CountTempX>50000){CountTempX=0;}
		   /*if(CountTempX>(CountTempXX[0]+4000)){}
		   else{
			   			CountTempXX[2]=CountTempXX[1];
			   			CountTempXX[1]=CountTempXX[0];
			   			CountTempXX[0]=CountTempX;
			   			CountTempXS= (CountTempXX[0]+ CountTempXX[1]+ CountTempXX[2])/3;
			   			 }
*/		   }
	   }

	   P1IE=0;TA1CTL&=~TAIE;

       if(		SampleXIFG==0){CountTempX=0;}
	   SetCursorPosition(0, 3);
	   PrintUInt(CountTempX);
	   SetCursorPosition(0, 15);
	   __delay_cycles(4000000);

	   CountIFG=1;CountTime=0;P1IE=(YAxis);TA1CTL|=TAIE;SampleCounter=0;
	   SampleYIFG=0;
       while(CountIFG)
       {
    	   if(SampleCounter<5){
    		   CountTempY=(1000000/(CountY1*2));if(CountTempY>50000){CountTempY=0;}
    	   }
       }

       P1IE=0;TA1CTL&=~TAIE;
       if(		SampleYIFG==0){CountTempY=0;}
       SetCursorPosition(2, 3);
       PrintUInt(CountTempY);
       SetCursorPosition(2, 15);
       __delay_cycles(4000000);
	   CountIFG=1;CountTime=0;P1IE=(XAxis);TA1CTL|=TAIE;SampleCounter=0;
	   SampleXIFG=0;

 }
}




#pragma vector=PORT1_VECTOR
__interrupt void port1(void)
{
	if((P1IFG&XAxis)==XAxis)
	{
	    CountX1=CountX;
		CountX&=0;
		SampleXIFG=1;
		SampleCounter++;
	}
	if((P1IFG&YAxis)==YAxis)
		{
		    CountY1=CountY;
			CountY&=0;
			SampleYIFG=1;
			SampleCounter++;
		}

	P1IFG=0;
}
#pragma vector=TIMER1_A1_VECTOR
__interrupt void EjeX_Timer(void)
{
	 TA1CTL&=~TAIFG;
	CountX++;
	CountY++;
//if(CountTime==250){CountIFG=0;CountTime=0;}{CountTime++;}
	if(CountTime==500){CountIFG=0;CountTime=0;}{CountTime++;}

}
