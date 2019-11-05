#include <msp430g2553.h>
#include"CDC.h"

#define LedPin BIT0
#define Nleds 138
/************************************VARIABBLE AND MACROS******************************************************/
unsigned int 		Vin=1020,Vmax=1020,VES1=510,VES2=612,VES3=795,Vout=100;



/*************************************FUNCTION DECLARATION******************************************************/
    void clk();
    void uart();
    void Enin();
char LedValue=0x80,LedRed,LedGreen,LedBlue=0x40,LedValueAux,LedNumber=0x08;
void ws2812(char);
void writeLed(char , char , char );
int main(void)
	{

	 volatile unsigned int i,ii;
	clk();
    	uart();
		Enin();

		DMACTL0=0;

  P2DIR|=LedPin;
  P2SEL&=~LedPin;
  P2SEL2&=~LedPin;
  P2OUT&=~LedPin;
  _delay_cycles(16000000);

  while(1)
		{

/*
	  for(i=0;i<=Nleds;i++){

	  //	ec("el numero de leds es");p_ui(Nleds);p_ui(i);clc_();

	  		writeLed(0x00,0x00,0x00);


	  }
	  P2OUT&=~LedPin;
	  _delay_cycles(1000000);
*/

for(ii=0;ii<=Nleds;ii++){
for(i=0;i<=Nleds;i++){

	//	ec("el numero de leds es");p_ui(Nleds);p_ui(i);clc_();
//		writeLed(LedRed,LedGreen,LedBlue);

	if((i)==(ii-1)){

		writeLed(LedRed,LedGreen,LedBlue);}

	else{
		writeLed(0,0,0);
	}
}
	P2OUT&=~LedPin;
_delay_cycles(500000);
}

		/*
	 	 	writeLed(0x10,0x10,0x00);
			writeLed(0x00,0x00,0x00);
			writeLed(0x00,0x00,0x00);
			writeLed(0x00,0x00,0x00);
			writeLed(0x00,0x00,0x00);
			P2OUT=0;
		      _delay_cycles(6000000);

				writeLed(0x10,0x10,0x00);
				writeLed(0x00,0x10,0x10);
				writeLed(0x00,0x00,0x00);
				writeLed(0x00,0x00,0x00);
				writeLed(0x00,0x00,0x00);

			      P2OUT=0;
			      _delay_cycles(6000000);

			      writeLed(0x10,0x10,0x00);
			      writeLed(0x00,0x10,0x10);
			      writeLed(0x10,0x00,0x10);
				  writeLed(0x00,0x00,0x00);
				  writeLed(0x00,0x00,0x00);
			      P2OUT=0;
			      _delay_cycles(6000000);

			     writeLed(0x10,0x10,0x00);
			     writeLed(0x00,0x10,0x10);
			     writeLed(0x10,0x00,0x10);
			     writeLed(0x10,0x00,0x00);
			     writeLed(0x00,0x00,0x00);
			     P2OUT=0;
			     _delay_cycles(6000000);

			     writeLed(0x10,0x10,0x00);
			     writeLed(0x00,0x10,0x10);
			     writeLed(0x10,0x00,0x10);
			     writeLed(0x10,0x00,0x00);
			     writeLed(0x00,0x00,0x10);
			     P2OUT=0;
			     _delay_cycles(6000000);

			     writeLed(0x00,0x00,0x00);
			     writeLed(0x00,0x00,0x00);
 		         writeLed(0x00,0x00,0x00);
				 writeLed(0x00,0x00,0x00);
				 writeLed(0x00,0x00,0x00);
			      P2OUT=0;
			      _delay_cycles(6000000);

*/

		}
	}
/***********************************END OF MAIN RUTINE**************************************************/



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

			//		if(((G>>i)&0x01)){P2OUT|=BIT1;_delay_cycles(12);P2OUT=0;_delay_cycles(2);}else{P2OUT|=BIT1;_delay_cycles(2);P2OUT=0;}
				}
		for(i=0;i<=7;i++)
				{

			ws2812(B>>i);

			//			if(((B>>i)&0x01)){P2OUT|=BIT1;_delay_cycles(12);P2OUT=0;}else{P2OUT|=BIT1;_delay_cycles(2);P2OUT=0;}
				}
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

	   void Enin()
	 		{
	 			_BIS_SR(GIE);
	 			__enable_interrupt();
	 			__bis_SR_register(GIE);
	 		}
	   void clk()
			{
				WDTCTL = WDTPW | WDTHOLD;
				BCSCTL1 =CALBC1_16MHZ;
				BCSCTL2 =0;
				DCOCTL = CALDCO_16MHZ;
			}

/*************************************INTERRUPT*******************************************/

	#pragma vector=USCIAB0RX_VECTOR
	__interrupt void RXserial_isr(void)
	{
		IFG2&=~UCA0RXIFG;
		LedValueAux=LedValue-'0';
		LedValue=UCA0RXBUF;
		if(LedValue==('s'-'0')){
		LedRed=LedBlue;
	    LedBlue=LedGreen;
		LedGreen=LedValueAux*100;
		}

		switch(LedValue)
		{


		case 'r':LedRed=LedValueAux*20;break;
		case 'g':LedGreen=LedValueAux*20;break;
		case 'b':LedBlue=LedValueAux*20;break;
		case 'L':LedNumber=LedValue;break;

		}
	}


