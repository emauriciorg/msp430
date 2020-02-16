#include <msp430g2553.h>
#include"CDC.h"
#include"lcd16x2.h"
volatile char DES=0;
volatile char sec_t=0,min_t=0,hour_t=0,day_t=0;
volatile unsigned int COUNTT=75,countt=0,count_t=0;
#define hora1 7
#define hora2 6
void uart_init()
{
	P1SEL |= ( BIT1|BIT2);
	P1SEL2 |= (BIT1| BIT2);
	UCA0CTL1 = UCSWRST;
	UCA0CTL1 |= UCSSEL_2;                     // SMCLK
	UCA0BR0 = 65;                            // 16MHz 9600 PREESCALAR
	UCA0BR1 = 3;                             //(UCAxBR0 + UCAxBR1 � 256)
	UCA0MCTL =2<<1;//UCBRS0;                        // Modulation UCBRSx = 1
	UCA0CTL1 &= ~UCSWRST;
	IE2 = UCA0RXIE;
}



		void enable_timer()
		{



					  TA1CTL	 = ID_2|TASSEL_2|MC_1;
					  TA1CCR0	 = 40;
					  TA1CCTL1 =OUTMOD_7| CCIE;
					  TA1CCR1=000;





		}


 void enable_interrupts()
 		{
 			_BIS_SR(GIE);
 			__enable_interrupt();
 			__bis_SR_register(GIE);
 		}
	void clk_init()
		{
			WDTCTL = WDTPW | WDTHOLD;
			BCSCTL1 =CALBC1_8MHZ;
			BCSCTL2 =0;
			DCOCTL = CALDCO_8MHZ;
		}



	int main(void)
	{
		clk_init();
		/***Setup of LCD********/
		LcdInicio();

		P2SEL2=0X00;
		P2SEL=0X00;
		P2DIR=0XFF;
		P2OUT=0;

		/*****end of lcd setup***/





		 //  P1SEL&=~(BIT7|BIT6);
		 //  P1SEL2&=~(BIT7|BIT6);

//		   P1DIR|=(BIT7|BIT6);
			ClearDisplay();
				SetCursorPosition(0, 0);
					  PrintStr("Temperatura ");Lph_ui(25);

		   		enable_interrupts();

	 	enable_timer();


		while(1){
			SetCursorPosition(2, 0);

			Lph_ui(day_t);putme(':'); Lph_ui(hour_t);putme(':'); Lph_ui(min_t);putme(':'); Lph_ui(sec_t);//c_lc();
			_delay_cycles(50000);//10000);
		}

	}



	/*LAYERS of the menu
	 *
	 *
	 ****************
	 *temperatura 25*------>layer one
	 * 00:00:00:00  *
	 ****************
	 *013456789abcdef
	 *
	 ****************
	 *temperatura 25*------>layer2 one
	 * 00:00:00:00  *
	 ****************	 *
	 *
	 *****************
	 *temperatura 25*------>layer three
	 * 00:00:00:00  *
	 ****************
	 *
	 *
	 *
	 *
	 * */

	#pragma vector=PORT1_VECTOR
	__interrupt void PORT1_isr(void)
	{

		switch(P1IFG&0X19)
		{

		case BIT0:;break; //set
		case BIT3:;break; //up
		case BIT4:;break; //down


		}

	}

#pragma vector=USCIAB0RX_VECTOR
	__interrupt void RXserial_isr(void)
	{
		IFG2&=~UCA0RXIFG;

		DES=UCA0RXBUF;


	switch(DES)
      {

        case 'q':{	if(COUNTT<95){COUNTT+=1;}	}break;
		case 'a':{	if(COUNTT>55){COUNTT-=1;}	}break;

		default: COUNTT=COUNTT;
       }

	}


#pragma vector=TIMER1_A1_VECTOR
	__interrupt void Timer1a1_isr(void)
	{

		TA1CCTL1&=~CCIFG;
		//P1OUT^=BIT7;

        if(countt<1001)
        {
        if(countt<COUNTT){P1OUT|=BIT7;}else{P1OUT&=~BIT7;}
        countt++;}else{countt=0;
        }

        if(count_t==50000)
        {
          count_t=0;

           if(sec_t==59)
			 {
			  sec_t=0;

			    if(min_t==59)
				 {
					min_t=0;

					if(hour_t==24)
					{
						hour_t=0;
						day_t+=1;

					}else{if((hour_t==hora1)||(hora2==hour_t)){/*mover huevos xor 2 angles*/}hour_t+=1;}

				 }else{ min_t+=1;}

			 }else{sec_t+=1;}

       }else{count_t++;}


	}


#pragma vector=TIMER0_A0_VECTOR
	__interrupt void Timer0a0_isr(void)
	{
		P1OUT^=BIT6;
		TACCTL0&=~CCIFG;
	//	if(countt<COUNTT){		P1OUT|=BIT7;}else{P1OUT&=~BIT7;}

		//if(countt<COUNTT3){countt++;}else{countt=0;}


	}
