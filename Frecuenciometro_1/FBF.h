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





void Enin()
{
_BIS_SR(GIE);
__enable_interrupt();
__bis_SR_register(GIE);
}

void DesEnin()
{
__disable_interrupt();
}
void clk()
{
WDTCTL = WDTPW | WDTHOLD;
BCSCTL1 =CALBC1_16MHZ;
BCSCTL2 =0;
DCOCTL = CALDCO_16MHZ;
}






#endif /* FBF_H_ */
