/*
 * CDC._UD=(datoint&0x000f);h
 *
 *  Created on: 18/10/2014
 *      Author: mauror
 *
 *      CDC is an acronym for Communication and Data Converter
 *      This library contains the functions necessary to handle in a easy way the
 *      transfer of data(char strings, decimal numer, hexadecimal, special character,etc.) in
 *      uart_init-mode, basically this library transform your int, unsigned int or  float in a
 *      string of char type variable, and send it for you.
 *
 *------------------------------FUNCTIONS-----------------------------
 *
 *
 *
 *
 */
#ifndef CDC_H_
#define CDC_H_

void uart_write_byte(char dato);
int string2int(char iamstring);
void readint(unsigned int dataSR);
void uart_send_string(char *string);
int twoc2dec(unsigned int twoc);
unsigned int c2ui( char *c2uc);
void s_pc();
void printlong(unsigned long longtochar);
void int2hex(unsigned int datoint);
void clc_();
void printint( int intchar1);
void printchar2c(unsigned int int2cchar);
void p_ui(unsigned int intchar1);
void printfloat(float twoto3);

void print_uint(unsigned int intchar1);
void line_jump();

#endif /* CDC_H_ */
