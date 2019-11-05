/**
* @file		interrupciones.h
* @author	Manuel Caballero
* @date 	2/2/2015
* @brief 	Variables de las rutinas de interrupción.
* \copyright
* 	AqueronteBlog@gmail.com
*
* Este archivo es propiedad intelectual del blog Aqueronte,
* cuya direccion web, es la siguiente:
*
* 	http://unbarquero.blogspot.com/
*
* Se permite cualquier modificacion del archivo siempre y cuando
* se mantenga la autoria del autor.
*/
#include <msp430.h>
#include <stdint.h>


// Prototipo de subrutina de interrupción
//void USCI0TX_ISR(void) 	__attribute__((interrupt(USCIAB0TX_VECTOR)));
//void P2_ISR(void) 		__attribute__((interrupt(PORT2_VECTOR)));


// Variable externa
volatile uint16_t TX_Buff;
volatile uint8_t	*pBuff;
