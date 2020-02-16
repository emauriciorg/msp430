#include <msp430g2553.h>
#include"CDC.h"
volatile char DES=0,flag11;
volatile unsigned int COUNTT=0,COUNTT3=5000,countt=0;

	void uart_init()
		{
					P1SEL |= ( BIT1|BIT2);
			P1SEL2 |= ( BIT1|	BIT2);
			UCA0CTL1 = UCSWRST;
			UCA0CTL1 |= 0x80;                     // SMCLK
			UCA0BR0 = 130;                            // 16MHz 9600 PREESCALAR
			UCA0BR1 = 6;                             //(UCAxBR0 + UCAxBR1 � 256)
			UCA0MCTL =0x0c;//UCBRS0;                        // Modulation UCBRSx = 1
			UCA0CTL1 &= ~UCSWRST;
			IE2 = UCA0RXIE;
		}


 void Timer_block()

{

	   TACTL	 = ID_1|TASSEL_2|MC_1; //UP mode
	   TACCR0	 = 10000;
	   TACCTL0 =OUTMOD_7| CCIE;
	   TACCR1=65000;

/*	   P2SEL&=~(BIT2|BIT3);
	   P2SEL2&=~(BIT2|BIT3);

	   P2DIR|=(BIT2|BIT3);
	   P2OUT=0;
	*/
	   }

		void enable_timer(char on_off)
		{

			if(on_off=='1')
			{

					   TA1CTL	 = ID_1|TASSEL_2|MC_1; //UP mode
					   TA1CCR0	 = 1;
					   TA1CCTL1 =OUTMOD_7| CCIE;
					   TA1CCR1=10000;


					   P2SEL&=~(BIT0|BIT1);
					   P2SEL|=BIT1;

					   P2SEL2&=~(BIT0 |BIT1);
					   P2DIR|=BIT0|BIT1;
					   P2OUT&=~BIT1;
			}else
			{
                 				   TA1CTL	=0;
								   TA1CCR0	=0;
								   TA1CCTL1 =0;
								   TA1CCR1  =0;

								   P2SEL&=~(BIT1);
								   P2SEL2&=~(BIT1);
								   P2DIR|=BIT1;
								   P2OUT&=~BIT1;
			}


		}


 void enable_interrupts()
 		{
 			_BIS_SR(GIE);
 			__enable_interrupt();
 			__bis_SR_register(GIE);
 		}
	void clk_init()
		{
			WDTCTL = WDTPW | WDTHOLD;                 // Stop WDT
			BCSCTL1 =CALBC1_16MHZ;
			BCSCTL2 =0x00;
			DCOCTL = CALDCO_16MHZ;
		}



	int main(void)
	{
		clk_init();

		uart_init();


		   P2SEL&=~(BIT2);
			   P2SEL2&=~(BIT2);


			   P2DIR|=BIT2;
			   P2OUT&=~BIT2;
		Timer_block();




		   /*	   P1DIR&=~(BIT6|BIT0);
		   P1OUT&=~(BIT6|BIT0);
		   P1IES=0;

		   P1IE|=(BIT6|BIT0);
		*/
		   		enable_interrupts();



		while(1){

			uart_send_string("T1 ");print_uint( COUNTT/*TACCR0*/);line_jump();
/*if(flag11==1){flag11=0;	uart_send_string("OZONO<");}
if(flag11==2){flag11=0;	uart_send_string("LUZ UV<");}
*/

		}

	}





#pragma vector=PORT1_VECTOR
	__interrupt void por1l_isr(void)
	{
		if(((P1IFG&BIT6)==BIT6)){
		flag11=1;
		}
		else{
			if(	(P1IFG&BIT0)==BIT0)
			{flag11=2;}
		    }
				P1IFG=0;
	}


#pragma vector=USCIAB0RX_VECTOR
	__interrupt void RXserial_isr(void)
	{
		IFG2&=~UCA0RXIFG;

		DES=UCA0RXBUF;


	switch(DES)
      {

        case 'q':{	COUNTT+=1;	}break;
		case 'a':{	COUNTT-=1;	}break;
		case 'z':{	COUNTT=000;	}break;



		case 'w':{	TACCR0+=100;}break;
		case 's':{  TACCR0-=100;}break;
		case 'x':{  TACCR0=6000;}break;
		case 'f':{  TACCR0=000;}break;


		//case '1':{	enable_timer('1');}break;
		//case '2':{ 	enable_timer('0');}break;

       }

	}


#pragma vector=TIMER1_A1_VECTOR
	__interrupt void Timer1a1_isr(void)
	{

		TA1CCTL1&=~CCIFG;

	}


#pragma vector=TIMER0_A0_VECTOR
	__interrupt void Timer0a0_isr(void)
	{

		TACCTL0&=~CCIFG;

	///	if(countt<COUNTT){		P2OUT=BIT2;}else{P2OUT&=~BIT2;}
		if(countt<COUNTT){countt++;}else{countt=0;P2OUT^=BIT2;}

		//P2OUT^=BIT2;
	}

