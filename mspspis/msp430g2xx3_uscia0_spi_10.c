
//******************************************************************************
//   MSP430G2xx3 Demo - USCI_A0, SPI 3-Wire Slave Data Echo
//
//   Description: SPI slave talks to SPI master using 3-wire mode. Data received
//   from master is echoed back.  USCI RX ISR is used to handle communication,
//   CPU normally in LPM4.  Prior to initial data exchange, master pulses
//   slaves RST for complete reset.
//   ACLK = n/a, MCLK = SMCLK = DCO ~1.2MHz
//
//   Use with SPI Master Incremented Data code example.  If the slave is in
//   debug mode, the reset signal from the master will conflict with slave's
//   JTAG; to work around, use IAR's "Release JTAG on Go" on slave device.  If
//   breakpoints are set in slave RX ISR, master must stopped also to avoid
//   overrunning slave RXBUF.
//
//                MSP430G2xx3
//             -----------------
//         /|\|              XIN|-
//          | |                 |
//          | |             XOUT|-
// Master---+-|RST              |
//            |             P1.2|<- Data Out (UCB0SOMI)
//            |                 |
//            |             P1.1|-> Data In (UCB0SIMO)
//            |                 |
//            |             P1.4|<- Serial Clock In (UCB0CLK)
//
//   D. Dang
//   Texas Instruments Inc.
//   February 2011
//   Built with CCS Version 4.2.0 and IAR Embedded Workbench Version: 5.10
//******************************************************************************
#include <msp430.h>
#include "CDC.h"

unsigned char DATANN='3';
void spimodule();
void uartmodule();
int main(void)
{

	WDTCTL = WDTPW | WDTHOLD;                 // Stop WDT
		BCSCTL1 =CALBC1_1MHZ;
		BCSCTL2 =0x00;
		DCOCTL = CALDCO_1MHZ;
		uartmodule();

		spimodule();

_BIS_SR(GIE);
__enable_interrupt();
__bis_SR_register(GIE);
while(1)
{

}

}

// Echo character
	#pragma vector=USCIAB0RX_VECTOR
	__interrupt void USCI0RX_ISR (void)
	{
		DATANN = UCB0RXBUF;

	}


	void uartmodule()
	{

		P1SEL |= BIT2;
		P1SEL2 |=  BIT2;
		UCA0CTL1 |= UCSWRST;
		UCA0CTL1 |= 0x80;                     // SMCLK
		UCA0BR0 = 104;                            // 16MHz 9600 PREESCALAR
		UCA0BR1 = 0;                             //(UCAxBR0 + UCAxBR1 × 256)
		UCA0MCTL =UCBRS1;                        // Modulation UCBRSx = 1
		UCA0CTL1 &= ~UCSWRST;
		IE2 |= UCA0TXIE;
	  UCA0TXBUF='R';

	}
	void spimodule(){

		while (!(P1IN & BIT5));                   // If clock sig from mstr stays low,
												// it is not yet in SPI mode
	  P1SEL |= BIT5 | BIT6 | BIT7;
	  P1SEL2 |= BIT5 | BIT6 | BIT7;
	  UCB0CTL1 =UCSWRST;                       // **Put state machine in reset**
	  UCB0CTL0 = UCCKPL | UCMSB| UCSYNC;      // 3-pin, 8-bit SPI
	  UCB0CTL1 &=~ UCSWRST;                     // **Initialize USCI state machine**
	  IE2 |= UCB0RXIE;                          // Enable USCI0 RX interrupt

	}

	#pragma vector=USCIAB0TX_VECTOR
	__interrupt void USCI0TX_ISR (void)
	{
		UCA0TXBUF=DATANN;

	}

