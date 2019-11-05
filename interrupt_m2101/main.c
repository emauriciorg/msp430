#include <msp430g2101.h>

void inicio_msp();
	void enable_interrupt()
	{

			_BIS_SR(GIE);
			__enable_interrupt();
			__bis_SR_register(GIE);
	}
	int main(void)
	{
inicio_msp();
enable_interrupt();
	}


			void inicio_msp()
			{
					/*Clock and Watchdog */
				WDTCTL=0X5A00|0X0080;
				BCSCTL1=CALBC1_1MHZ;
				BCSCTL2=0;
				DCOCTL=CALDCO_1MHZ;
					/*PORT*/
				P1DIR=(0X3F); //LED OUTPUT+SOUND SPEAKER
				P1SEL=0X00;
				P1OUT=0X00;



					P2DIR&=~(0XC0); //SHOW AND SETUP
					P2SEL&=~(0XC0);
					P2REN|=0XC0;  //pull down
					P2IES|=0XC0;  //rise edge
					P2IE|=0XC0;   //interrupt enable
					P2OUT=0XC0;
			}
	#pragma vector=PORT4_VECTOR
	__interrupt void p2_isr()
	{


		switch(P1IFG)
		{
		case BIT6:P1OUT^=BIT1;;break;  /*Display mode*/
		case BIT7:P1OUT|=BIT0;break;	/*Control mode*/

		default: P1OUT|=4;

		}
P1IFG=0;
	}



