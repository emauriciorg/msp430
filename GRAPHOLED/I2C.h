/*
 * GYRO.h
 *
 *  Created on: 1/01/2015
 *      Author: Mauricio
 *
 */

#ifndef I2C_H_
#define I2C_H_

#define WHO_AM_I            0X0F         //R
#define CTRL_REG1          	0X20         //RW
#define CTRL_REG2          	0X21         //RW
#define CTRL_REG3          	0X22         //RW
#define CTRL_REG4          	0X23         //RW
#define CTRL_REG5          	0X24         //RW
#define REFERENCE	       		0X25         //RW
#define OUT_TEMP           	0X26        //R
#define STATUS_REG         	0X27        //R
#define OUT_X_L            		0X28        //R
#define OUT_X_H           		0X29       	//R
#define OUT_Y_L            		0X2A       //R
#define OUT_Y_H            	0X2B        //R
#define OUT_Z_L            		0X2C       //R
#define OUT_Z_H            	0X2D       //R
#define  FIFO_CTRL_REG    0X2E        //RW
#define  FIFO_SCR_REG      0X2F        //R
#define  INT1_CFG          		0x30        //RW
#define  INT1_SRC          		0x31       //R
#define INT1_TSH_XH        0x32        //RW
#define INT1_TSH_XL        	0x33        //RW
#define INT1_TSH_YH        0x34        //RW
#define INT1_TSH_YL        	0x35        //RW
#define INT1_TSH_ZH        0x36        //RW
#define INT1_TSH_ZL        	0x37        //RW
#define INT1_DURATION  	0x38       //RW

#define SADLR   0xD5	//SLAVEADRESSLOW     READ
#define SADLW	0XD4	//SLAVEADRESSLOW     WRITE

#define SADHR	0X6B	//SLAVEADRESSHIGH    READ 110 101+sd0

unsigned char TXDATAI2C;


void initI2C(void);

void initI2C(void)
{
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

//EN LA TARGET L3GD20 EL PIN SDO EL CUAL ES EL BIT DE MENOR PESO EN EN LA DIRECCION ESTA EN 1. SE USARA  SADH

void I2CWrite(unsigned char AGR, unsigned char V2R )//
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

unsigned int I2CRead(unsigned int AGR)
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



#endif /* I2C_H_ */

