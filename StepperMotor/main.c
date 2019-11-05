#include <msp430g2553.h>
#include "FBF.h"
#include "CDC.h"
#include"StepMotor.h"/*
 * main.c
 */

volatile char PositionA=0,PositionB=0;
volatile char DES=0,Rifg=0;

 void main(void) {
   InitConfig();
   InitStepperMotor();
   InitInterrupts();
while(1)
{



ec("Position ");EnviarDato(PositionA+'0');s_pc();EnviarDato(PositionB+'0');clc_();
if(Rifg==1){rotate();}else{
SendStepperMotor(PositionA,PositionB);}

}

}


//  1


#pragma vector=USCIAB0RX_VECTOR
__interrupt void RXserial_isr(void)
{
	IFG2&=~UCA0RXIFG;
	DES=UCA0RXBUF;
	Rifg=0;
	switch(DES)
	{
		case '0':{PositionA=0;}break;
		case '1':{PositionA=1;}break;
      	case '2':{PositionA=2;}break;
		case '3':{PositionA=3;}break;
                             ;
		case 'q':{PositionB=0;}break;
		case 'w':{PositionB=1;}break;
		case 'e':{PositionB=2;}break;
		case 'd':{PositionB=3;}break;
		case 'r':{Rifg=1;}break;

	}
}

