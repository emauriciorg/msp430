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
 *      uart_init
 *      i2c master mode
 *
 */

#ifndef FBF_H_
#define FBF_H_
#include<msp430.h>
void SetClk(void);
void ADCInit(void);
void AdcFBF(void);
void I2CReceiver(void);
void I2Ctransmitter(void);
void EnableInterrupts(void);
void PortConf(void);
void ExternalInterrupt(void);
void ExternalEvents(void);
void Timer0Conf(void);
void Timer3Conf(void);
void SetClk(void);
void InitMcuConf(void);

#endif /* FBF_H_ */
