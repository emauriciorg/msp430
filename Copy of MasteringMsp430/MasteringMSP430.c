
/*
 * Author:Mauricio RIos
 *
 *
 * This file contains all the code necesarry to drive the Functional block mentioned on FBF.h
 *
 * It is to necessary to uncomment certain isr depend on the block that you going to use
 *Every block has its resplectable comment which says the instructions to use it.
 * */
#include <msp430.h> 
#include"CDC.H"
#include"FBF.h"


#define SEGA BIT7
#define SEGB BIT6
#define SEGC BIT5
#define SEGD BIT4
#define SEGE BIT3
#define SEGF BIT2
#define SEGG BIT1
#define DOT  BIT0
unsigned char uni,deci;
unsigned char dataa;
void writeDisplay(unsigned char);
void muxDisplay(unsigned char);
const char seg[]={0x01,0x02,0x04,0x10,0x20,0x40,0x80};
//unsigned char TXData,RXData;

void main(void){
//	unsigned int i;
	inicio();
P1OUT=0XFF;
inicioADC();
while(1)
{
muxDisplay(dataa);

}
	
}

void muxDisplay(unsigned char num)
{

    deci=num/10;
    uni=num-(deci*10);
    P1OUT=0;
    writeDisplay(deci);
    P1OUT=BIT3;
	_delay_cycles(5000);
	P1OUT=0;
	writeDisplay(uni);
	P1OUT=BIT0;
	_delay_cycles(5000);

}
void writeDisplay(unsigned char num)
	{

	switch(num)
	{
	case 0:     P2OUT=~0xFC;break;
	case 1:     P2OUT=~0X60; break;
	case 2:     P2OUT=~0xDA;break;
	case 3:     P2OUT=~0xF2;break;
	case 4:     P2OUT=~0x66;break;
	case 5:     P2OUT=~0xB6;break;
	case 6:     P2OUT=~0xBE;break;
	case 7:		P2OUT=~0xE0;break;
	case 8:		P2OUT=~0xFE;break;
	case 9:		P2OUT=~0xF6;break;
	case '.':	P2OUT=~0x01;break;
	default:P2OUT=0x90;
	}

	}

#pragma vector=ADC10_VECTOR
__interrupt void ADC10_ISR (void)
{
 ADC10CTL0&=~ADC10IFG;
 dataa=(ADC10MEM*330/1024);
 /*if(count==4){count=0;volt=volt/4;ec("voltaje ");espacio();printint(volt);borrar();
}else{count++;volt=ADC10MEM+volt;}
 */
}


/* timer0 please define this  unsigned char timer0count=0;
#pragma vector=TIMER0_A0_VECTOR
__interrupt void timer0_a0(void){

	TA0CCTL0&=0xfffe;
	TA0CTL&=0xfffe;//0X02D2;

if(timer0count==10){timer0count=0;P1OUT^=0X01;}else{timer0count++;}
}
*/


/*
 * Timer3, please define this unsigned char timer1count=0;
#pragma vector=TIMER1_A0_VECTOR
__interrupt void timer1_a0(void){

	TA1CCTL0&=0xfffe;
	TA1CTL&=0xfffe;--replace this with the respectly variable
if(timer1count==10){timer1count=0;P1OUT^=0X40;}else{timer1count++;}
}

*/

/*uart mode

#pragma vector = USCIAB0TX_VECTOR
__interrupt void USCIAB0TX_ISR(void)
{
   UCB0TXBUF=TXData;                       // Get RX data

}

#pragma vector = USCIAB0RX_VECTOR
__interrupt void USCIAB0RX_ISR(void)
{
  RXData = UCB0RXBUF;                       // Get RX data

}

*/


/* This part is made for i2c transmit master mode
 Please define this unsigned char i2xflagaux=0;

 #pragma vector=USCIAB0TX_VECTOR
__interrupt void transmiterI2C(void){

	//clear flags

IFG2&=~UCB0TXIFG;//INTERRUPT FLAG REGISTER

UCB0TXBUF=TXData;
if(i2xflagaux==1){
UCB0CTL1 |= UCTR + UCTXSTT;
i2xflagaux=0;
}

//while (UCB0CTL1 & UCTXSTP);             // Ensure stop condition got sent
                // I2C TX, start condition

}

#pragma vector=USCIAB0RX_VECTOR
__interrupt void receiverI2c(void){
	//clear flags
	IFG2&=~UCB0RXIFG;
	UCB0STAT&=~UCSTTIFG ;
	i2xflagaux=1;

}
 *
 * */

