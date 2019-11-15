/*
 * GYRO.h
 *
 *  Created on: 1/01/2015
 *      Author: Mauricio
 *
 */

#ifndef GYRO_H_
#define GYRO_H_

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

//EN LA TARGET L3GD20 EL PIN SDO EL CUAL ES EL BIT DE MENOR PESO EN EN LA DIRECCION ESTA EN 1. SE USARA  SADH

void gw(unsigned char AGR, unsigned char V2R );
unsigned int gr(unsigned int AGR);




#endif /* GYRO_H_ */
