#include <msp430g2553.h>
#include"CDC.h"// uart library---prints numbers, ascii, hex, bin ,strings....
#include"Timer.h"//generates delay functions based on timer
#include"DHT11.h"


/************************************VARIABLES AND MACROS******************************************************/

volatile char DES=0;

	void readSensor();

	void clk();
	void uart();
	void Enin();



	int main(void)
	{

		clk();
		uart();
	 	Enin();

	 	P1SEL&=~BIT0;
	 	P1SEL2&=~BIT0;
	 	P1DIR|=BIT0;
	 	P1OUT|=BIT0;

	 	while(1)
		{

	 		ec("DATA ");p_ui(byte0);s_pc();p_ui(byte1);s_pc();p_ui(byte2);s_pc();p_ui(byte3);s_pc();p_ui(byte4);clc_();



		}
	}



	void clk()
				{
					WDTCTL = WDTPW | WDTHOLD;
					BCSCTL1 =CALBC1_16MHZ;
					BCSCTL2 =0;
					DCOCTL = CALDCO_16MHZ;
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

	

	   void Enin()
	 		{
	 			_BIS_SR(GIE);
	 			__enable_interrupt();
	 			__bis_SR_register(GIE);
	 		}

	void readSensor()
	{
		Ndata1=0;
		DTH11_data();
		P1DIR|=(BIT0);//set p1.0 as output   1-output  0-input

	}


#pragma vector=USCIAB0RX_VECTOR
__interrupt void RXserial_isr(void)
{
	IFG2&=~UCA0RXIFG;
	DES=UCA0RXBUF;

	/*byte0=0;
	byte1=0;
    byte2=0;
    byte3=0;
    byte4=0;
	 */
		if(DES== 'a'){	readSensor();	}

}
