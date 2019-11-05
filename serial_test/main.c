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

default:numb_c=0;}
return numb_c;
}


int main(void)
{
	inicio();
	while(1)
	{
		PrintInt(PWMCOUNT);clc();
	}
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
			case 'b':PWMCOUNT=0;break;
			case 'd':PWMCOUNT=150;break;
			default: PWMCOUNT=0;break;

			}

		}else{
			PWMCOUNT=((char_to_int(DES[0]))+(10*(char_to_int(DES[1]))))*3;
		}



	}

