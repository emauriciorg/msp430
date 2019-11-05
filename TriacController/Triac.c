#include <msp430G2553.h>
#include "FBF.h"
#include "CDC.h"
/*
 * main.c
 */
unsigned char P1FLAG=(BIT3|BIT0);
volatile unsigned int PWMCOUNT=0,count;
char DES[2]={'a','a'};
unsigned char BIT0_M=0;
volatile unsigned int conteo=0;
volatile unsigned int countair=0,arsped1,arsped2=0,arsped3=0;
int char_to_int(char numb_c)
{

switch(numb_c){
case'0':numb_c=0;break;
case'1':numb_c=1;break;
case'2':numb_c=2;break;
case'3':numb_c=3;break;
case'4':numb_c=4;break;
case'5':numb_c=5;break;
case'6':numb_c=6;break;
case'7':numb_c=7;break;
case'8':numb_c=8;break;
case'9':numb_c=9;break;

default:numb_c=0;P2OUT&=~BIT2;}
return numb_c;
}




int main(void)
{
	inicio();

						TACTL	 = ID_2|TASSEL_2|MC_1; //UP mode
						TACCR0	 = 10;
						TACCTL0 = CCIE;





}



#pragma vector=PORT2_VECTOR
__interrupt void port2ISR(void)
{

if(P2IFG&BIT0){
	countair=0;


}
P2IFG=0;
}






#pragma vector=USCIAB0RX_VECTOR
	__interrupt void RXserial_isr(void)
	{
		IFG2&=~UCA0RXIFG;
		DES[1]=DES[0];
		DES[0]=UCA0RXBUF;
		if((DES[0]>'9')||(DES[1]>'9')){

			switch(DES[0])
			{

			case 'a':PWMCOUNT=1;break;
			case 'x':PWMCOUNT=0; P2OUT&=~BIT2;break;
			case 'd':PWMCOUNT=150;break;
			default: PWMCOUNT=0; P2OUT&=~BIT2;break;

			}

		}else{
			PWMCOUNT=((char_to_int(DES[0]))+(10*(char_to_int(DES[1]))))*3;
		}



	}


#pragma vector=TIMER0_A0_VECTOR
	__interrupt void Timer0a1_isr(void)
	{



//	if(TACCTL0&CCIFG){

		TACCTL0&=~CCIFG;
		if(PWMCOUNT>0){
	  if(countair<=PWMCOUNT){  //pwm max 305
		  P2OUT&=~BIT2;

	   }else{P2OUT|=BIT2;
}
	  if(countair==410){P2OUT&=~BIT2;countair=0;}else{countair++;}

		  }
		}
  // }


