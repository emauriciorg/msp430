/*
 * GYRO.h
 *
 *  Created on: 1/01/2015
 *      Author: Mauricio
 *
 */

#ifndef DS1307_H_
#define DS1307_H_

#define secc            0X00         //R
#define minn          	0X01         //RW
#define horr         	0X02         //RW
#define diaa         	0X03         //RW
#define datt         	0X04         //RW
#define monn        	0X05         //RW
#define yeaa       		0X06         //RW
#define RTC_control     0X07        //R




#define SADLR   0xD5	//SLAVEADRESSLOW     READ
#define SADLW	0XD4	//SLAVEADRESSLOW     WRITE

#define SADHR	0X6B	//SLAVEADRESSHIGH    READ 110 101+sd0

unsigned char TXDATAI2C;

//EN LA TARGET L3GD20 EL PIN SDO EL CUAL ES EL BIT DE MENOR PESO EN EN LA DIRECCION ESTA EN 1. SE USARA  SADH

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

unsigned char gr(unsigned char AGR)
{
	//UCB0I2CSA = SADHR;
	unsigned char RXDATAI2C=0;
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



#endif /* DS1307_H_ */

