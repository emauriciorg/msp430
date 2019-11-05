/*
 * nrf24l01p.h
 *
 *  Created on: 08/03/2017
 *      Author: Mauricio
 */

#ifndef NRF24L01P_H_
#define NRF24L01P_H_

#include <msp430G2553.h>
#define SpiCSN BIT0
#define SpiCE BIT1
/*********COMMANDS DEFINITIONS***************/
#define R_REGISTER    0x00 //first 5 bits are the register address
#define W_REGISTER    0x20 //first 5 bits are the register address
#define R_RX_PAYLOAD  0x61 //
#define W_TX_PAYLOAD  0xA0
#define FLUSH_TX      0xC1
#define FLUSH_RX      0xC2
#define REUSE_TX_PL   0xC3
#define R_RX_PL_WID   0x60
#define W_ACK_PAYLOAD 0xA8
#define W_TX_PAYLOAD_NOACK  0xB0
#define DO_NOP        0XFF
/********REGISTERs DEFINITIONS****************/
#define R_CONFIG     0X00
#define R_EN_AA      0X01
#define R_EN_RXADDR  0X02
#define R_SETUP_AW   0X03
#define R_SETUP_RETR 0X04
#define R_RF_CH      0X05
#define R_RF_SETUP   0X06
#define R_STATUS     0X07
#define R_OBSERVE_TX 0X08
#define R_RPD        0X09
#define R_RX_ADDR_P0 0X0A
#define R_RX_ADDR_P1  0X0B
#define R_RX_ADDR_P2  0X0C
#define R_RX_ADDR_P3  0X0D
#define R_RX_ADDR_P4  0X0E
#define R_RX_ADDR_P5  0X0F
#define R_TX_ADDR     0X10
#define R_RX_PW_P0    0X11
#define R_RX_PW_P1    0X12
#define R_RX_PW_P2    0X13
#define R_RX_PW_P3    0X14
#define R_RX_PW_P4    0X15
#define R_RX_PW_P5    0X16
#define R_FIFO_STATUS 0X17
#define R_DYNPD       0X1C
#define R_FEATURE     0X1D

extern volatile char nRfStatus;
extern char DataRegR[7];
extern char DataReg[7];
extern char PayLoadToSend[7];
extern char DataRegW[7];
void InitNrf(void);
void SpiInit(void);
void SpiWrite(char, char);
void SpiWriteReg(char, char,char);
void SpiSendPayLoad();
char SpiRead(char);
void SpiReadReg(char,char );
void SpiwaitT(void);
void SpiwaitR(void);
void SpiSendCommand(char); /****************/

#endif /* NRF24L01P_H_ */
