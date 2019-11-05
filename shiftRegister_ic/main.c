#include <msp430.h>

#define DATA BIT0 // DS -> 1.0
#define CLOCK BIT4 // SH_CP -> 1.4
#define LATCH BIT5 // ST_CP -> 1.5

unsigned    char i ,x_x,yy, bin;
 long testm=0;
void delay(unsigned int ms)
{
 while (ms--)
    {
        __delay_cycles(1000); // set for 16Mhz change it to 1000 for 1 Mhz
    }
}
void sammi();
void SendSR8(char,char,char,char);
void SendSR(long);
void simplem();
int main( void )
{

  WDTCTL = WDTPW | WDTHOLD;      // Stop WDT
  BCSCTL1 =CALBC1_1MHZ;
  BCSCTL2 =0x00;
  DCOCTL = CALDCO_1MHZ;

  P1DIR = DATA | CLOCK |LATCH;
  P1SEL=0X00;
  P1SEL2=0X00;

  P1OUT = 0X00;   // RESET ALL
  while(1)
  {
//	  simplem();
  //sammi();

//   RGB
	//   SendSR8(0,4,((~(0x01<<yy))&0xFF),0x03<<x_x);
	SendSR(0xFFFF0003);
	_delay_cycles(400);

	SendSR(0xFF00FF0C);
	_delay_cycles(400);

	SendSR(0x00FFFF30);
	_delay_cycles(400);

	SendSR(0xFFFF00C0);
	SendSR(0xFF00FFC0);

  }

}

void sammi()
{


	 for( yy=0;yy<8;yy++)
	 {
		  for(  x_x=0; x_x<8;x_x++)
		  {
			  	  // R G B C			  C R B C	      C R G B



		  testm=(0X00000001<<x_x)|((~(0x01000000))&0xFFFFFF00);

		//   SendSR8(0,4,((~(0x01<<yy))&0xFF),0x03<<x_x);

		SendSR(testm);
		  _delay_cycles(300000);
		  }
		 }


}

void simplem()
{


	 for( yy=0;yy<8;yy++)
	 {
		  for(  x_x=0; x_x<8;x_x++)
		  {
			  	  // R G B C			  C R B C	      C R G B



		  testm=(0X0001<<x_x)|((0x0100<<x_x));




		         for(i = 0 ; i <= 15 ; i++)
		         {
		      	   P1OUT&=~DATA;
		      	   P1OUT|=(testm>>i)&DATA;

		      	   _delay_cycles(100);
		      	   P1OUT |= CLOCK;
		      	   _delay_cycles(100);
		  		   P1OUT &= ~CLOCK;


		  }
		         _delay_cycles(400);
		         P1OUT |= LATCH;
		         P1OUT &= ~LATCH;
		         _delay_cycles(100000);

		 }



}
}
void SendSR(long SRData)
{

       for(i = 0 ; i <= 31 ; i++)
       {
    	   P1OUT&=~DATA;
    	   P1OUT|=(SRData>>i)&DATA;

    	   _delay_cycles(50);
    	   P1OUT |= CLOCK;
    	   _delay_cycles(50);
		   P1OUT &= ~CLOCK;

       }
//waits for 4 times clock cicle
       _delay_cycles(200);
       P1OUT |= LATCH;
       P1OUT &= ~LATCH;

}

void SendSR8(char mred,char mgre,char mblu,char mcol)
{


       for(i = 0 ; i <= 7 ; i++)
       {
    	   P1OUT&=~DATA;
    	   P1OUT|=(mcol>>i)&DATA;

    	   _delay_cycles(100);
    	   P1OUT |= CLOCK;
    	   _delay_cycles(100);
		   P1OUT &= ~CLOCK;

       }


       for(i = 0 ; i <= 7 ; i++)
       {
    	   P1OUT&=~DATA;
    	   P1OUT|=(mred>>i)&DATA;

    	   _delay_cycles(100);
    	   P1OUT |= CLOCK;
    	   _delay_cycles(100);
		   P1OUT &= ~CLOCK;

       }

       for(i = 0 ; i <= 7 ; i++)
       {
    	   P1OUT&=~DATA;
    	   P1OUT|=(mgre>>i)&DATA;

    	   _delay_cycles(100);
    	   P1OUT |= CLOCK;
    	   _delay_cycles(100);
		   P1OUT &= ~CLOCK;

       }

       for(i = 0 ; i <= 7 ; i++)
       {
    	   P1OUT&=~DATA;
    	   P1OUT|=(mblu>>i)&DATA;

    	   _delay_cycles(100);
    	   P1OUT |= CLOCK;
    	   _delay_cycles(100);
		   P1OUT &= ~CLOCK;

       }
//waits for 4 times clock cicle
       _delay_cycles(400);
       P1OUT |= LATCH;
       P1OUT &= ~LATCH;


}


