#include <msp430.h>
#include "CDC.h"
unsigned char MST_Data[11]={'1','2','3','4', '5','6','7','8','9',13,13};
unsigned char SLV_Data[11]={'h','o','l','a', 'm','u','n','d','o',13};
unsigned char nnn=0;
unsigned char datap=0;

void spimodule();
void uartmodule();

int main(void)
{
  volatile unsigned int i;

  WDTCTL = WDTPW | WDTHOLD;                 // Stop WDT
  	BCSCTL1 =CALBC1_1MHZ;
  	BCSCTL2 =0x00;
  	DCOCTL = CALDCO_1MHZ;


  	spimodule();
//  	uartmodule();



  __bis_SR_register(  GIE);       // CPU off, enable interrupts

}

		#pragma vector=USCIAB0TX_VECTOR
		__interrupt void USCIA0TX_ISR(void)
		{

			if(datap==10){datap=0;}else{datap++;}
			UCB0TXBUF=MST_Data[datap];
			__delay_cycles(75);
		}

		void uartmodule()
		{
				P1SEL |= ( BIT2);
				P1SEL2 |= ( BIT2);
				UCA0CTL1 = UCSWRST;
				UCA0CTL1 |= 0x80;                     // SMCLK
				UCA0BR0 = 6;//104;                            // 16MHz 9600 PREESCALAR
				UCA0BR1 = 0;                             //(UCAxBR0 + UCAxBR1 × 256)
				UCA0MCTL =0x40;                        // Modulation UCBRSx = 1
				UCA0CTL1 &= ~UCSWRST;
				IE2 |= UCA0TXIE;

		}
		void spimodule(){

	  P1OUT = 0x00;                             // P1 setup for LED & reset output
	  P1DIR |= BIT4;                     //
	  P1SEL |= BIT5 + BIT6 + BIT7;
	  P1SEL2 |= BIT5 + BIT6 + BIT7;

	  UCB0CTL1 =UCSWRST;
	  UCB0CTL0 |= (UCCKPL | UCMSB | UCMST | UCSYNC);  // 3-pin, 8-bit SPI master
	  UCB0CTL1 |= UCSSEL_2;                     // SMCLK
	  UCB0BR0 |= 0x02;                          // /2
	  UCB0BR1 = 0;                              //
	  UCA0MCTL = 0;                             // No modulation
	  UCB0CTL1 &= ~UCSWRST;                     // **Initialize USCI state machine**
	  IE2 |= UCB0TXIE;                          // Enable USCI0 RX interrupt

	  P1OUT &= ~BIT4;                           // Now with SPI signals initialized,
	  P1OUT |= BIT4;                            // reset slave

	  __delay_cycles(75);                 // Wait for slave to initialize

	//  UCB0TXBUF='A';
	}
