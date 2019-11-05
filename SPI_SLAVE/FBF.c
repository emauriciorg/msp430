/*
 * FBF.c
 *
 *  Created on: 12/03/2017
 *      Author: Mauricio
 */


#include"FBF.h"

void ADCInit(){	ADC10CTL0 |= (ENC | ADC10SC);}
void AdcFBF()
{
	ADC10CTL1 =INCH_1|ADC10SSEL_2|CONSEQ_3 	|ADC10DIV_7;        // Channel 5, ADC10CLK/4
	ADC10CTL0 = ADC10SHT_3|MSC|ADC10IE|ADC10ON|ADC10SR|REFBURST;
	ADC10AE0 = 0x0003;                        //P1.5 ADC optionç
}

void I2CReceiver()
{
 P1SEL |= BIT6 + BIT7;                     // Assign I2C pins to USCI_B0
 P1SEL2|= BIT6 + BIT7;                     // Assign I2C pins to USCI_B0
 UCB0CTL1 |= UCSWRST;                      // Enable SW reset
 UCB0CTL0 = UCMODE_3 + UCSYNC;             // I2C Slave, synchronous mode
 UCB0I2COA = 0x48;                         // Own Address is 048h
 UCB0CTL1 &= ~UCSWRST;                     // Clear SW reset, resume operation
 IE2 |= UCB0RXIE;                          // Enable RX interrupt
}


void I2Ctransmitter()
{
	  P1SEL |= BIT6 + BIT7;                     // Assign I2C pins to USCI_B0
	  P1SEL2|= BIT6 + BIT7;                     // Assign I2C pins to USCI_B0
	  UCB0CTL1 |= UCSWRST;                      // Enable SW reset
	  UCB0CTL0 = UCMST + UCMODE_3 + UCSYNC;     // I2C Master, synchronous mode
	  UCB0CTL1 = UCSSEL_2 + UCSWRST;            // Use SMCLK, keep SW reset
	  UCB0BR0 = 12;                             // fSCL = SMCLK/12 = ~100kHz
	  UCB0BR1 = 0;
	  UCB0I2CSA = 0x48;                         // Slave Address is 048h
	  UCB0CTL1 &= ~UCSWRST;                     // Clear SW reset, resume operation
	  IE2 |= UCB0TXIE;                          // Enable TX interrupt
      //TXData = 0x00;                            // Holds TX data
}

void EnableInterrupts()
{
	_BIS_SR(GIE);
	__enable_interrupt();
	__bis_SR_register(GIE);
}

void PortConf()
{
	P1DIR=BIT0;
	P1OUT=0X00;
	P1SEL&=~(BIT0);
	P1SEL2&=~BIT0;
}
void Externalinterrupt()
{
	P1IE=BIT3; //Habilita la interrupcion asociada a P1IFG
	P2IFG=0X00; // set when a interrupt ocurrs
	P1REN=0;
	P2IES=0X00; // INTERRUPT EDGE SELECT  EDGE SELECTS THE INTERRUPT EDGE FOR THE CORRESPONDIN I/O, 0 MEANS low-to-high transition, 1 means a high-to-low transition
    P1OUT=0;
}
void ExternalEvents()
{
// this function recieve the input in rising/fall/both edges and store the count when it happend and when it ends, after that it gives to you a to values of
//	count event one and event two it is on p2.0 pin which is the cci1 from timer3, this pin is on pull-down resistor.see times and etc.
 P2OUT=0X00;
 P2DIR&=(~0X01);
 P2SEL|=0X01;
 P2SEL2&=(~0X01);
 P2REN=0X00;
 TA1CTL=ID_3|TASSEL_2|MC_2;
 TA1CCTL0=CAP|CM_3|CCIE|SCS;
}

void Timer0Conf()
{
	TA0CCR0=60000;
	TACCTL0=CCIE; //no capture mode+CCIA+Asynchronous en capture mode+modo comparacion+
	TACTL=ID_3|TASSEL_2|MC_1|TAIE;
}

void Timer3Conf()
{
	TA1CCR0=20000;
	TA1CCTL0=CCIE; //no capture mode+CCIA+Asynchronous en capture mode+modo comparacion+
	TA1CTL=ID_3|TASSEL_2|MC_1|TAIE;
}

void SetClk(void)
{
  WDTCTL = WDTPW | WDTHOLD;                 // Stop WDT
  BCSCTL1 =CALBC1_16MHZ;
  BCSCTL2 =0x00;
  DCOCTL = CALDCO_16MHZ;
}
void InitMcuConf()
{
	PortConf();
	EnableInterrupts();
}
