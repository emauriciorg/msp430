/*
 * FBF.h
 *
 *  Created on: 6/11/2014
 *      Author: mauricio
 */
#ifndef FBF_H_
#define FBF_H_



void timer0(void);
void canal(unsigned int soyuncanal);
void Adc(void);
void inicioADC(void);

void Enableinterrupts(void);
void digitalio(void);
void configport1(void);
void configport2(void);
void uart(void);
void clk(void);
void port1interrupt(void);
void port2interrupt(void);
void eventosexternos(void);
void i2cmaster(void);
void inicio(void);

#endif /* FBF_H_ */
