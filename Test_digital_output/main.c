#include <msp430.h> 
#include "CDC.h"
#include "FBF.h"
char charIN=0;
		/*
		 * main.c
		 */
		int main(void)
		{

		inicio();
		while(1)
		{

			switch(charIN)
						{
						case'0':P2OUT=0X01;P1OUT|=0X01;break;
						case'1':P2OUT=0X02;P1OUT|=0X02;break;
						case'2':P2OUT=0X04;P1OUT|=0X04;break;
						case'3':P2OUT=0X08;P1OUT|=0X08;break;
						case'4':P2OUT=0X10;P1OUT|=0X10;break;
						case'5':P2OUT=0X20;P1OUT|=0X20;break;
						case'6':P2OUT=0X40;P1OUT|=0X40;break;
						case'7':P2OUT=0X80;P1OUT|=0X80;break;
						default:P2OUT=0X00;P1OUT=0X00;break;
						}






					}

		}
		#pragma vector=USCIAB0RX_VECTOR
		__interrupt void SerialReceiver_ISR(void )
		{
			IFG2&=~UCA0RXIFG;

			charIN=UCA0RXBUF;

		}
