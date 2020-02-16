/*
 * CDC._UD=(datoint&0x000f);h
 *
 *  Created on: 18/10/2014
 *      Author: mauricio
 *
 *      CDC is an acronym for Communication and Data Converter
 *      This library contains the functions necessary to handle in a easy way the
 *      transfer of data(char strings, decimal numer, hexadecimal, special character,etc.) in
 *      uart_init-mode, basically this library transform your int, unsigned int or  float in a
 *      string of char type variable, and send it for you.
 *
 *------------------------------FUNCTIONS-----------------------------
 *ESPACIO();
 *BORRAR();
 *
 *
 *
 *
 */
#ifndef CDC_H_
#define CDC_H_

#include<msp430.h>

extern char aux_char[7];
extern  char signo;
extern unsigned char _UD,_U,_D,_UM,_C,_DM;
extern unsigned long u,d,c,um,dm,cm,uM,dM,cM;
extern unsigned int auxSR;
extern volatile char UartInput;
/*Function List
 *
 * line_jump();
 * espacio();
 * c2ui();
 * printstr();
 * uart_write_byte();
 * int2hex();
 * printchar2c();
 * printfloar();
 * printlong();
 * print_uint();
 * readint();
 * twoc2dec();
 * string2int();
 *
 * */
unsigned int C2UInt( char *);
void ClearTerminal(void);
void Int2Hex(unsigned int);
void UartMenu(char);
void PrintInt(int);
void PrintStr(char *);
void SingleChar(char);
void PrintFloat(float);
void PrintMenu(void);
void PrintLong(unsigned long );
void PrintUInt(unsigned int );
void SingleSpace(void);
void LineFeed(void);
int  String2Int(char);
int  TwoC2Dec(unsigned int);
void UartConf(void);
#endif /* CDC_H_ */
