/**
* @file		main.c
* @author	Manuel Caballero
* @date 	17/2/2015
* @brief 	Archivo principal.
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
//#include "variables.h"
#include "funciones.h"
#include "interrupciones.h"
#include "NRF24L01.h"



/**
 *  \brief     void main( void )
 *  \details   Este programa consiste en leer datos de forma inalámbrica usando el dispositivo
 *  		   nRF24L01+.
 *
 *  		   Una vez lea dichos datos, se mandarán por la UART activándo el LED1 ( LED Rojo de
 *  		   la Launchpad ).
 *
 *  		   El microcontrolador estará en modo bajo consumo ( LPM4 ) y no despertará hasta que el
 *  		   dispositivo nRF24L01+ indique que ha recibido datos para leer.
 *
 *
 *  \author    Manuel Caballero
 *  \version   0.0
 *  \date      17/2/2015
 *  \pre       El código presente es SOLO para el RECEPTOR.
 *  \pre	   El dispositivo nRF24L01+ se conecta al periférico USCI_B0 en modo SPI del microcontrolador.
 *  \pre	   Asegurarse de que el LED1 ( LED Rojo ) está conectado al pin P1.0.
 *  \pre	   Asegurarse de que que concuerden las siguientes señales:
 *
 *  				- CE   ( nRF24L01+ ):	P2.0
 *  				- CSN  ( nRF24L01+ ):	P2.1
 *  				- #IRQ ( nRF24L01+ ):	P2.2
 *
 *  \pre	   Code Composer Studio, Version: 6.0.1.00040.
 *  \pre	   C Compiler, MSP430 GCC GNU v4.9.1.
 */
void main( void )
{
  conf_WDT      ();                // Configura WDT del sistema
  conf_CLK      ();                // Configura CLK del sistema
  conf_IO       ();                // Configura Entradas/Salidas
  conf_SPI_B0   ();                // Configura USCI_B0 --> SPI
  conf_UART		();				   // Configura Uart

  nRF24L01_init ();				   // Configura nRF24L01+


  __enable_interrupt();            // Interrupciones ON.


  while(1)
  {
	LPM4;

	P1OUT	|=	BIT0;			  // LED1 ON

	pBuff 	 = 	nRF24L01_WriteRead (R_REGISTER, R_RX_PAYLOAD, 0, 2);	// Lectura del nRF24L01+ ( 2-Bytes )
	nRF24L01_reset ();													// Reset a flags ( registro STATUS )

	TX_Buff  =	1;
	IE2     |=  UCA0TXIE;     	   // Interrupción Tx ON ( empieza a enviar paquetes por la UART )
  }
}
