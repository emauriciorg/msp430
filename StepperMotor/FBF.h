/*
* FBF.h
*
*  Created on: 28/01/2015
*      Author: Mauricio Rios
*
*
*
*
*      The FBF is and abreviation for FuntionalBlockFunctions, this header file contain almost all
*      the software necessary for drive the Msp430's Funtional Block, every drive is set on interrupt mode.
*
*      Blocks included:
*      I/O interrupts,pull-up/down resistor,
*      Analog almost all channels with a single reading or multi-reading
*      Timer0 and Timer3
*      pwm,capture/compare
*      uart
*      i2c master mode
*
*/

#ifndef FBF_H_
#define FBF_H_



void InitDigitalIO(void);
void InitInterrupts(void);
void DesEnin(void);
void InitClk(void);
void InitConfig(void);
void InitUart(void);
void InitInterrupts(void)
{
_BIS_SR(GIE);
__enable_interrupt();
__bis_SR_register(GIE);
}

void InitUart(void)
{
 P1SEL |= ( BIT1|BIT2);
 P1SEL2 |= (BIT1| BIT2);
 UCA0CTL1 = UCSWRST;
 UCA0CTL1 |= UCSSEL_2;                     // SMCLK
 UCA0BR0 = 130;//65;                            // 16MHz 9600 PREESCALAR
 UCA0BR1 = 6;//3;                             //(UCAxBR0 + UCAxBR1 × 256)
 UCA0MCTL =6<<1;//UCBRS0;                        // Modulation UCBRSx = 1
 UCA0CTL1 &= ~UCSWRST;
 IE2 = UCA0RXIE;
}

void InitClk(void)
{
WDTCTL = WDTPW | WDTHOLD;
BCSCTL1 =CALBC1_16MHZ;
BCSCTL2 =0;
DCOCTL = CALDCO_16MHZ;
}

void InitDigitalIO(void)
{

P2SEL=0;
P2DIR=0X0F;
P2SEL2=0;
P2OUT=0;

}


void InitConfig(void)
{

InitClk();
//InitDigitalIO();
InitUart();
}



#endif /* FBF_H_ */
