/*
 * nrf24l01p.c
 *
 *  Created on: 12/03/2017
 *      Author: Mauricio
 */
#include"nrf24l01p.h"

volatile char nRfStatus =0;
char DataRegR[7]={0};
char DataReg[7]={0};
char PayLoadToSend[7]={'S','3','1','4','e'};
char DataRegW[7]={0xE9,0x00,0x33,0x11,0x77};


void SpiInit()
{
  UCB0CTL1= UCSWRST;
  UCB0CTL1|=UCSSEL_2; //SMCLK as the FBRCLK
  UCB0BR0=2; //FBITCLOCK=FBRCLK/UCBRX; 4khz
  UCB0BR1=0X00;
  UCB0CTL0=(UCMSB|UCMST|UCCKPH|UCSYNC);

  P1DIR|=BIT0;
  P1SEL  |=(BIT5|BIT6|BIT7);
  P1SEL2|=(BIT5|BIT6|BIT7);

  P2DIR=SpiCSN|SpiCE;
  P2SEL=0;
  P2SEL2=0;
  P2OUT=SpiCSN;
  P1OUT|=BIT0;
  IFG2&=~(UCB0TXIFG|UCB0RXIFG);
  UCB0CTL1&=~UCSWRST;
}
void SpiwaitT(){while((IFG2&UCB0TXIFG)==0);}
void SpiwaitR(){while((IFG2&UCB0RXIFG)==0);}
void InitNrf(void)
{
  SpiInit();
  _delay_cycles(1000000);
  SpiWrite(R_CONFIG,0X4B);//MASK_MAX_RT, TXmode,PwrUP
  SpiWriteReg(R_EN_RXADDR,0xff,5);
  SpiWriteReg(R_RX_PW_P0,32,1);
  P2OUT|=SpiCE;   //set RX address both should match (RXaddr and Txaddr)
}

void SpiSendPayLoad()
{
	volatile char ireg=0;
	P2OUT&=~SpiCSN;
	P1OUT&=~BIT0;
	P2OUT|=SpiCE;
    while(P2IN&SpiCE==SpiCE);
	SpiwaitT();
	UCB0TXBUF=(W_TX_PAYLOAD);
	SpiwaitT();
	SpiwaitR();
	nRfStatus=UCB0RXBUF;
	for(ireg=0;ireg<5;ireg++)
	{
		SpiwaitT();
		UCB0TXBUF=(PayLoadToSend[ireg]);
	}
	SpiwaitT();
	UCB0TXBUF=DO_NOP;
	P2OUT|=SpiCSN;
	P1OUT|=BIT0;
}
void SpiWriteReg( char SpiRegw,char SpiDataf,char W_bytes)
{

	/*char *dataregwf;

	dataregwf=SpiRegw;
	for(ireg=0;ireg<W_bytes;ireg++)
	{
		dataregwf++;
	}
	*/
	volatile char ireg=0;
	P2OUT&=~SpiCSN;
	P1OUT&=~BIT0;
	SpiwaitT();
	UCB0TXBUF=(SpiRegw|0X20);
	SpiwaitT();
	SpiwaitR();
	nRfStatus=UCB0RXBUF;
	for(ireg=0;ireg<W_bytes;ireg++)
	{
		SpiwaitT();
		UCB0TXBUF=(DataRegW[ireg]);
	}
	SpiwaitT();
	UCB0TXBUF=DO_NOP;
	P2OUT|=SpiCSN;
	P1OUT|=BIT0;
}

/*************Writes a single byte*/
void SpiSendCommand(char nRfCommand)
{
	P2OUT&=~SpiCSN;
	P1OUT&=~BIT0;
	SpiwaitT();
	UCB0TXBUF=(nRfCommand);
	SpiwaitT();
	SpiwaitR();
	nRfStatus=UCB0RXBUF;
	SpiwaitT();
	UCB0TXBUF=DO_NOP;
/************Added to send 2 bytes */
	SpiwaitT();
	UCB0TXBUF=DO_NOP;
	P2OUT|=SpiCSN;
	P1OUT|=BIT0;
}
void SpiWrite( char SpiRegw,char SpiDataf)
{
	P2OUT&=~SpiCSN;
	P1OUT&=~BIT0;
	SpiwaitT();
	UCB0TXBUF=(SpiRegw|0X20);
	SpiwaitT();
	SpiwaitR();
	nRfStatus=UCB0RXBUF;
	SpiwaitT();
	UCB0TXBUF=(SpiDataf);
	//_delay_cycles(100);/*******************************************+*/
	SpiwaitT();
	UCB0TXBUF=DO_NOP;
/************Added to send 2 bytes */

	SpiwaitT();
	UCB0TXBUF=(SpiDataf);
	//_delay_cycles(100);/*******************************************+*/
	SpiwaitT();
	UCB0TXBUF=DO_NOP;
	P2OUT|=SpiCSN;
	P1OUT|=BIT0;
}
char SpiRead(char SpiRegr)
{
	volatile int SpiReadr=0;
	P2OUT&=~SpiCSN;
	P1OUT&=~BIT0;
	SpiwaitT();
	UCB0TXBUF=SpiRegr;
	SpiwaitT();
	SpiwaitR();
	nRfStatus=UCB0RXBUF;  //Status reception
 /**************************/
	SpiwaitT();
	UCB0TXBUF=DO_NOP;
/***********************/

    SpiwaitR();
    SpiReadr=UCB0RXBUF;
  	P2OUT|=SpiCSN;
	P1OUT|=BIT0;
	return SpiReadr;
}

void SpiReadReg(char SpiReg,char R_bytes)
{
	volatile char ireg=0;
	P2OUT&=~SpiCSN;
	P1OUT&=~BIT0;

	SpiwaitT();
	UCB0TXBUF=SpiReg;
	SpiwaitT();
	SpiwaitR();
	nRfStatus=UCB0RXBUF;

	for(ireg=0;ireg<R_bytes;ireg++)
	{
	 SpiwaitT();
	 UCB0TXBUF=DO_NOP;
     SpiwaitR();
      DataRegR[ireg]=UCB0RXBUF;
	}
	P2OUT|=SpiCSN;
	P1OUT|=BIT0;

}




