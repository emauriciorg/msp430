	#include <msp430.h>
		#include"CDC.h"
		#include"FBF.h"
		#include<math.h>

#define DO  221
#define RE  123
#define MI  172
#define FA  100
#define SOL 50
#define LA  89
#define SI  10
#define BUZZER  BIT2


		unsigned int Ncp=60000;
		unsigned char P2OUTaux,N1;
		float freqq;


#define KData	BIT0
#define KClk	BIT1
unsigned int KeyPress=0;
unsigned int KeyPressAux=0;

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


		unsigned int byteRx,byteRxold;
		unsigned char changeT=0;
		unsigned int tcount=0;
		unsigned char isenu,isenun;
		//unsigned char inote=0;
		void noteformula(float note);

		void main(void)
		{
			inicio();
			  KeyboardSetup();

			  P1DIR|=BIT0;
			  P1SEL&=~BIT0;
			  P1SEL2&=~BIT0;
			  P1OUT&=~BIT0;

				enable_interrupts();

			while(1)	{

//				byteRx='1';

			uart_send_string("ESPERANDO ");print_uint(byteRx);line_jump();
			}

		}



		void noteformula( float note)
		{
			freqq=powf(0.5,note/12);
			N1=(110/freqq);
			Ncp=36363.63*freqq;//(4525.45)
		  //Ncp=568*freqq;
		}

		void servo(int ser1){
	volatile int SerOK=0;

	 	   TACTL	 = ID_3|TASSEL_2|MC_1; //UP mode
		   TACCR0	 = 40;//20us
		   TACCTL0 =OUTMOD_7;
		   TACCR1=0;

		 do{

			while((TACCTL0&CCIFG)!=CCIFG);

			TACCTL0&=~CCIFG;

			if(countt<ser1){P2OUT=BUZZER;}else{P2OUT&=~BUZZER;}//SERVO1

			//76
			if(countt<1001){countt++;}else{countt=0;SerOK++;}



		 }while(SerOK!=10);
	   	   countt=0;
			TACCTL0|=TACLR;
			G_IRA=0;
			SerOK=0;
	}







		#pragma vector= USCIAB0RX_VECTOR
		__interrupt void RX_vector (void)
		{
			_BIC_SR(GIE);
			IFG2&=UCA0RXIFG;
			byteRx=UCA0RXBUF;
			if(byteRx=='z'){changeT=0;}
			if(('0'<=byteRx)){changeT=1;}else{byteRx='1';}
			_BIS_SR(GIE);
		}


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
				KeyPressAux=(KeyPress>>1)&~(0x100);
				byteRx=KeyPressAux+'0';
				changeT=1;
				KeyPress=0;
				P1OUT&=~BIT0;

		}

	}
	P2IFG=0;


}
