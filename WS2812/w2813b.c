/*!
   \file ws2813b
   \brief "Description"
   \author "Your name"
   \date "DD"/"Month"/"Year"
*/
#include "ws2813b.h"


void ws2812(char bit_1)
{
	if(((bit_1)&0x01))
	{
		P2OUT|=LedPin;	_delay_cycles(12);	P2OUT=0;
	}
	else
	{
		P2OUT|=LedPin;	_delay_cycles(2);	P2OUT=0;
	}

}


void writeLed( char R, char G, char B)
{
	volatile char i=0;

	for(i=0;i<=7;i++)
	{
		ws2812(G>>i);
	}

	for(i=0;i<=7;i++)
	{
		ws2812(R>>i);

		/*		if(((G>>i)&0x01)){
			P2OUT|=BIT1;
			_delay_cycles(12);
			P2OUT=0;
			_delay_cycles(2);
		}else{P2OUT|=BIT1;
		_delay_cycles(2);
		P2OUT=0;}
		*/
	}

	for(i=0;i<=7;i++)
	{

		ws2812(B>>i);

		/*
			if(((B>>i)&0x01)){
			P2OUT|=BIT1;
			_delay_cycles(12);
			P2OUT=0;
			}else{
			P2OUT|=BIT1;
			_delay_cycles(2);
			P2OUT=0;
			}
		*/
	}
}
