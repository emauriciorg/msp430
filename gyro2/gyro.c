#include "GYRO.h"


void gw(unsigned char AGR, unsigned char V2R )//
{
	while (UCB0CTL1 & UCTXSTP);
    UCB0CTL1 |= (UCTR | UCTXSTT);
    while((IFG2&UCB0TXIFG)==0);
    UCB0TXBUF  =AGR;
    while((IFG2&UCB0TXIFG)==0);
    UCB0TXBUF  =V2R;
    while((IFG2&UCB0TXIFG)==0);
    while (UCB0CTL1 & UCTXSTT);
	UCB0CTL1 |=  UCTXSTP;
}

unsigned int gr(unsigned int AGR)
{
	//UCB0I2CSA = SADHR;
	unsigned int RXDATAI2C=0;
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
