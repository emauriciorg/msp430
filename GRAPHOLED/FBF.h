	/*
	 * FBF.h
	 *
	 *  Created on: 6/11/2014
	 *      Author: mauricio
	 */

	#ifndef FBF_H_
	#define FBF_H_

	void inicio(void);
	void	clk(void);
	void Uart(void);
	void Enin(void);

	void Uart()
		{
			P1SEL |= ( BIT1|BIT2);
			P1SEL2 |= ( BIT1|	BIT2);
			UCA0CTL1 = UCSWRST;
			UCA0CTL1 |= 0x80;                     // SMCLK
			/*UCA0BR0 = 130;                            // 16MHz 9600 PREESCALAR
			UCA0BR1 = 6;                             //(UCAxBR0 + UCAxBR1 × 256)
			*/
			UCA0BR0 = 130;                            // 16MHz 9600 PREESCALAR
			UCA0BR1 = 6;                             //(UCAxBR0 + UCAxBR1 × 256)

			UCA0MCTL =0x0c;                        // Modulation UCBRSx = 1
			UCA0CTL1 &= ~UCSWRST;
			IE2 &=~ UCA0RXIE| UCA0TXIE;
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
			BCSCTL2 =0x00;
			DCOCTL = CALDCO_16MHZ;
		}



	void inicio()
	{
		clk();
		Uart();
	    Enin();
	}


	#endif /* FBF_H_ */
