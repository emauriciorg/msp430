#include <msp430.h> 

/*
 * main.c
 */

unsigned char slaveAdress;

	void gw(unsigned char AGR, unsigned char V2R )//
	{
		//uart_send_string("sending request ");
		UCB0I2CSA = SADHW;
		while (UCB0CTL1 & UCTXSTP);
		//uart_send_string("stp");
		UCB0CTL1 |= (UCTR | UCTXSTT);

		if(UCNACKIFG&UXB0STAT){UCB0I2CSA = SADHW;}else{uart_send_string("encontrado en ")}

		while((IFG2&UCB0TXIFG)==0);
		UCB0TXBUF  =AGR;
	  //  uart_send_string(" dta");

		while((IFG2&UCB0TXIFG)==0);
		UCB0TXBUF  =V2R;
		//uart_send_string(" dtv");

		while((IFG2&UCB0TXIFG)==0);
		//uart_send_string(" tbe");

		while (UCB0CTL1 & UCTXSTT);
		//uart_send_string(" stt");

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
