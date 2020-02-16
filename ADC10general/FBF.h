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

void ADC10f();
void initADC10();
void I2CReceiver();
void I2Ctransmitter();
void enable_interrupts();
void configport();

void uart_init();
void clk_init();
void interrupcion();
void external_events_init();
void timer0();
void configtimer3();

#endif /* FBF_H_ */
