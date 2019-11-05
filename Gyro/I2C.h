#ifndef I2C_H_
#define I2C_H_


// address 0x6b
void I2CMaster(){

	  P1SEL |= BIT6 + BIT7;                     // Assign I2C pins to USCI_B0
	  P1SEL2|= BIT6 + BIT7;                     // Assign I2C pins to USCI_B0

	  UCB0CTL1 |= UCSWRST;                      // Enable SW reset

	  UCB0CTL0 = UCMST + UCMODE_3 + UCSYNC;     // I2C Master, synchronous mode
	  UCB0CTL1 = UCSSEL_2 + UCSWRST;            // Use SMCLK, keep SW reset
	  UCB0BR0 = 160;                             // fSCL = SMCLK/12 = ~100kHz
	  UCB0BR1 = 0;

	  UCB0I2CSA = 0x48;                         // Slave Address is 048h

	  UCB0CTL1 &= ~UCSWRST;                     // Clear SW reset, resume operation
	 // IE2 |= UCB0TXIE;                          // Enable TX interrupt

	  //TXData = 0x00;                            // Holds TX data
}


//The UCBxTXIFG is set when a star condition is generated
	char Read_i2c(char sla, char regii2c)
	{
	    //sent continuous uctxstt for receive, uctr may be clear
		UCB0I2CSA = sla;                         // Slave Address is 048h
		UCB0CTL1 |=UCTR;            // Use SMCLK, keep SW reset
		while(UCB0TXIFG==0);
		UCB0TXBUF=datta;
							//and setting UCTXSTT

		  	  	  	  	  	  //the UCBxRXIFG set when recieved
	}
// acknowledge interrupt flag	UCNACKIFG  set id not aknw is  declared for the slave , stop ot star procedures
char write_i2c(char sla, char regii2c, char datta)
	{

	//UCBxTXIFG  sets when data is onto the shift register
		  UCB0I2CSA = sla;                         // Slave Address is 048h
		  UCB0CTL1 |=UCTR;            // Use SMCLK, keep SW reset
		  //and setting UCTXSTT
 		  UCB0TXBUF=datta;

	}

#endif
