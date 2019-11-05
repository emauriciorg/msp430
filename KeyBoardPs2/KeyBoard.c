	#include <msp430.h>
	#include "FBF.h"
	#include "CDC.h"/*
	 * main.c
	 */
	#define KData	BIT0
	#define KClk	BIT1
	unsigned int KeyPress=0;
	unsigned int KeyPressAux=0,KeyPressAuxOld=0,KeyPressAuxOld1=0;

	char DataBit=0;


	void KeyboardSetup()
	{
	P2DIR&=~(KClk|KData);
	P2SEL&=~(KClk|KData);
	P2SEL2&=~(KClk|KData);

	P2IE|=KClk; //Habilita la interrupcion asociada a P1IFG
	P2IFG=0X00; // set when a interrupt ocurrs
	P2IES|=KClk; // INTERRUPT EDGE SELECT  EDGE SELECTS THE INTERRUPT EDGE FOR THE CORRESPONDIN I/O, 0 MEANS low-to-high transition, 1 means a high-to-low transition


	}


	int main(void)
	{

	  inicio();
	  KeyboardSetup();

	  P1DIR|=BIT0;
	  P1SEL&=~BIT0;
	  P1SEL2&=~BIT0;
	  P1OUT&=~BIT0;
	  Enin();
	  while(1)
	  {


		  ec("el valor de la tecla en decimal  es ");p_ui((KeyPressAux)); enviardato(' ');p_ui((KeyPressAuxOld)); enviardato(' ');p_ui((KeyPressAuxOld1));borrar();

	  }

	}

	/*
	   0 xxxx xxxx 1 -> 1 xxxx xxxx 0
     space     --82   52
     g-		   --104  68


	 2-r 32 72 --740  2e4

	     b0011 0010- m0111 0010,  0010 1110 0100

							 op-       0111 0010

	      	  	  	  	  	 in-        0011 1010

									   0011 0010


	      	  	  	  	  	   274
	 1-i 31 69 --772  304

	     b 0011 0001- m 0101 1001,  0011 0000 0100

							 op-        1000 0010

	      	  	  	  	  	 in-        0100 0001

									    0011 0001



	 0-p 30 70 --224 e0

	 b-2 62-32 --100 64

	 n-1 6e-31  --98 62
	*/

	#pragma vector=PORT2_VECTOR
	__interrupt void Port2_isr(void)
	{

		P1OUT|=BIT0;

		if(P2IFG&KClk)
		{

			if(DataBit<10)
			{
				KeyPress|=(P2IN&KData)<<DataBit;
				DataBit++;
			}
			else{
					DataBit=0;
					KeyPressAuxOld1=KeyPressAuxOld;
					KeyPressAuxOld=KeyPressAux;
					KeyPressAux=(KeyPress>>1)&~(0x100);
					KeyPress=0;
					P1OUT&=~BIT0;

			}

		}
		P2IFG=0;

	
	}
