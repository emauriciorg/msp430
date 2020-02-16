#include <msp430g2553.h>
#include"CDC.h"
volatile char DES=0,flag11,side_t='0',I_I=0;
volatile unsigned int COUNTT=75,COUNTT3=5000,countt=0;

void uart()
{
P1SEL |= ( BIT1|BIT2);
P1SEL2 |= (BIT1| BIT2);
UCA0CTL1 = UCSWRST;
UCA0CTL1 |= UCSSEL_2;                     // SMCLK
UCA0BR0 = 130;                            // 16MHz 9600 PREESCALAR
UCA0BR1 = 6;                             //(UCAxBR0 + UCAxBR1 � 256)
UCA0MCTL =6<<1;//UCBRS0;                        // Modulation UCBRSx = 1
UCA0CTL1 &= ~UCSWRST;
IE2 = UCA0RXIE;
}



void en_timer(char on_off)
{

	if(on_off=='1')
	{

			   TA1CTL	 = ID_3|TASSEL_2|MC_1; //UP mode
			   TA1CCR0	 = 40;
			   TA1CCTL1 =OUTMOD_7| CCIE;
			  TA1CCR1=000;


			/*   P2SEL&=~(BIT1);
			   P2SEL|=BIT1;

			   P2SEL2&=~(BIT1);
			   P2DIR|=BIT1;
			   P2OUT&=~BIT1;
	*/
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


void Enin()
	{
		_BIS_SR(GIE);
		__enable_interrupt();
		__bis_SR_register(GIE);
	}
void clk()
{
	WDTCTL = WDTPW | WDTHOLD;                 // Stop WDT
	BCSCTL1 =CALBC1_16MHZ;
	BCSCTL2 =0;
	DCOCTL = CALDCO_16MHZ;
}

void girar(char );

int main(void)
{
clk();

uart();





   P1SEL&=~(BIT7|BIT6);
   P1SEL2&=~(BIT7|BIT6);

   P1DIR|=(BIT7|BIT6);


   		Enin();

	en_timer('1');


while(1){
ec("q+=5  a-=5 ");printuint(COUNTT);borrar();


}

}



void girar(char SIDE_T )
{
	if(I_I==1)
	{
		I_I=0;
		switch(SIDE_T)
		{
		case'R':if(COUNTT<92){COUNTT++;}break;
		case'L':if(COUNTT>65){COUNTT--;};break;
		case'Z':COUNTT=75;break;

		}

   }else{I_I=1;}
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
case 'R':{	side_t='R';}	break;
case 'L':{	side_t='L';}break;
case 'Z':{	side_t='Z';}break;

}

}


#pragma vector=TIMER1_A1_VECTOR
__interrupt void Timer1a1_isr(void)
{

TA1CCTL1&=~CCIFG;
//P1OUT^=BIT7;
if(countt<COUNTT){P1OUT|=BIT7;}else{P1OUT&=~BIT7;}
if(countt<1001){countt++; }else{countt=0;girar(side_t);}

}


#pragma vector=TIMER0_A0_VECTOR
__interrupt void Timer0a0_isr(void)
{
P1OUT^=BIT6;
TACCTL0&=~CCIFG;
//	if(countt<COUNTT){		P1OUT|=BIT7;}else{P1OUT&=~BIT7;}

//if(countt<COUNTT3){countt++;}else{countt=0;}


}
