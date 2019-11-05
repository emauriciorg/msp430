#include <msp430.h> 

/*
 * main.c
 */

unsigned char slaveAdress;

	void gw(unsigned char AGR, unsigned char V2R )//
	{
		//ec("sending request ");
		UCB0I2CSA = SADHW;
		while (UCB0CTL1 & UCTXSTP);
		//ec("stp");
		UCB0CTL1 |= (UCTR | UCTXSTT);

		if(UCNACKIFG&UXB0STAT){UCB0I2CSA = SADHW;}else{ec("encontrado en ")}

		while((IFG2&UCB0TXIFG)==0);
		UCB0TXBUF  =AGR;
	  //  ec(" dta");

		while((IFG2&UCB0TXIFG)==0);
		UCB0TXBUF  =V2R;
		//ec(" dtv");

		while((IFG2&UCB0TXIFG)==0);
		//ec(" tbe");

		while (UCB0CTL1 & UCTXSTT);
		//ec(" stt");

		UCB0CTL1 |=  UCTXSTP;
		UCB0I2CSA = SADHR;
	}

	char gr(char AGR)
	{

		char RXDATAI2C=0;

		while (UCB0CTL1 & UCTXSTP);


		UCB0CTL1 |= (UCTR | UCTXSTT); //start

		while((IFG2&UCB0TXIFG)==0);
		UCB0TXBUF  =AGR;
		while((IFG2&UCB0TXIFG)==0);//transmision
		UCB0CTL1 &=~UCTR;
		UCB0CTL1 |= (UCTXSTT);//|UCTXNACK);
		while (UCB0CTL1 & UCTXSTT);
		UCB0CTL1 |=  UCTXSTP;//stop
		while((IFG2&UCB0RXIFG)==0);//reading
		RXDATAI2C = UCB0RXBUF;



							return(RXDATAI2C);
	}





int main(void) {
    WDTCTL = WDTPW | WDTHOLD;	// Stop watchdog timer
	
	return 0;
}
