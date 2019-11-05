#include <msp430g2553.h>
#include"CDC.h"
/************************************VARIABBLE AND MACROS******************************************************/
unsigned int 		Vin=1020,Vmax=1020,VES1=510,VES2=612,VES3=795,Vout=100;



/*************************************FUNCTION DECLARATION******************************************************/
    void clk();
    void uart();
    void Enin();

void ws2812(char);
void writeLed(char , char , char );
int main(void)
	{
		clk();
    	//uart();
		//Enin();


  P2DIR=0X0F;
  P2SEL=0;
  P2SEL2=0;
  P2OUT=0;
  _delay_cycles(16000000);

  while(1)
		{



			writeLed(0x01,0x01,0x00);
			writeLed(0x00,0x00,0x00);
			writeLed(0x00,0x00,0x00);
		      P2OUT=0;
		      _delay_cycles(4000000);

				writeLed(0x01,0x01,0x00);
				writeLed(0x00,0x01,0x01);
				writeLed(0x00,0x00,0x00);


			      P2OUT=0;
			      _delay_cycles(4000000);

			      writeLed(0x01,0x01,0x00);
			      writeLed(0x00,0x01,0x01);
			      writeLed(0x01,0x00,0x10);

			      P2OUT=0;
			      _delay_cycles(4000000);

			      writeLed(0x00,0x00,0x00);
			      writeLed(0x00,0x00,0x00);
			      writeLed(0x00,0x00,0x00);
			      P2OUT=0;
			      _delay_cycles(4000000);


			       //enviardato(read_button());s_pc();p_ui(Vin);s_pc();p_ui(Vmax);s_pc();p_ui(VES1);s_pc();p_ui(VES2);s_pc();p_ui(VES3);clc_();



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
					P2OUT|=BIT1;	_delay_cycles(12);	P2OUT=0;
				}
				else
				{
					P2OUT|=BIT1;	_delay_cycles(2);	P2OUT=0;
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
/*
	#pragma vector=USCIAB0RX_VECTOR
	__interrupt void RXserial_isr(void)
	{
		IFG2&=~UCA0RXIFG;
		DES=UCA0RXBUF;
		switch(DES)
		{
			case '1':{ Vin=510;	}break;
			case '2':{ Vin=612;	}break;
			case '3':{ Vin=795;	}break;
			case '4':{ Vin=1020;  }break;
		}
	}

*/
