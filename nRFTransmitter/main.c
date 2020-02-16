/**
* @file		main.c
* @author	Manuel Caballero
* @date 	4/2/2015
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
#include "variables.h"
#include "funciones.h"
#include "interrupciones.h"
#include "NRF24L01.h"



/**
 *  \brief     void main( void )
 *  \details   Este programa consiste en realizar una lectura de datos del sensor interno
 *  		   de temperatura cada, aproximadamente 3 segundos y enviarlos inal�mbricamente
 *  		   usando el dispositivo nRF24L01+.
 *
 *  		   En caso de que el env�o sea satisfactorio, el LED1 ( LED Rojo de la Launchpad),
 *  		   realizar� un parpadeo de, aproximadamente 0.1 s.
 *
 *  \author    Manuel Caballero
 *  \version   0.0
 *  \date      4/2/2015
 *  \pre       El c�digo presente es SOLO para el TRANSMISOR.
 *  \pre	   El dispositivo nRF24L01+ se conecta al perif�rico USCI_B0 en modo SPI del microcontrolador.
 *  \pre	   Asegurarse de que el LED1 ( LED Rojo ) est� conectado al pin P1.0.
 *  \pre	   Asegurarse de que que concuerden las siguientes se�ales:
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
  uint8_t *pBuff;


  conf_WDT      ();                // Configura WDT del sistema
  conf_CLK      ();                // Configura CLK del sistema
  conf_IO       ();                // Configura Entradas/Salidas
  conf_SPI_B0   ();                // Configura USCI_B0 --> SPI

  nRF24L01_init ();				   // Configura nRF24L01+

  conf_ADC10 	();				   // Configura ADC10 ( Sensor Interno Temperatura )
  conf_TA0		();				   // Configura TimerA TA0


  __enable_interrupt();            // Interrupciones ON.


  while(1)
  {
	//LPM3;
	//NOP();


	switch ( OpFlow ){
	case opRESET:
	// Realiza un Reset ( registro STATUS ) al nRF24L01+ ( es necesario cuando se ha enviado o recibido un paquete )
		nRF24L01_reset ();

		TA0CCR0 = 12;		                			// TAIFG on around ~ 1 ms
		TA0CTL  = TASSEL_1 + MC_1 + TACLR + TAIE;		// ACLK, upmode
		break;

	case opuart_write_bytes:
	// Env�a paquetes
		pBuff = &W_Buffer [ 0 ];
		nRF24L01_send ( pBuff, 2 );						// Env�a temperatura interna ( 2-Bytes )

		TA0CCR0 = 12;		                			// TAIFG on around ~ 1 ms
		TA0CTL  = TASSEL_1 + MC_1 + TACLR + TAIE;		// ACLK, upmode
		break;

	case opCheckTx:
	// Comprueba que la transmisi�n ha sido un �xito
		*pBuff = RESET;
		pBuff = nRF24L01_WriteRead (R_REGISTER, STATUS, 0, 1);

		if ( ( *pBuff & MAX_RT ) != 0 || ( *pBuff & TX_DS ) == 0 )
		{
		// Tx Fallo: No se ha enviado el dato o ACK no recivido.
			*pBuff = ERROR;
		}

		TA0CCR0 = 12;		                			// TAIFG on around ~ 1 ms
		TA0CTL  = TASSEL_1 + MC_1 + TACLR + TAIE;		// ACLK, upmode
		break;

	case opLED:
	// Act�a el estado del LED1 ( si OK, enciende LED1 - Rojo - )
		if ( *pBuff == ERROR )
			P1OUT	&=	~BIT0;
		else
			P1OUT	|=	 BIT0;

		TA0CCR0 = 1200;		                			// TAIFG on around ~ 0.1 s
		TA0CTL  = TASSEL_1 + MC_1 + TACLR + TAIE;		// ACLK, upmode
		break;

	default:
	case opTemInterna:
	// Vuelta a empezar: lectuta temperatura interna + reset nRF24L01+ + env�o de datos + cambio LED
	// cada ~ ( 3s - 46us - 1ms - 1ms - 1ms - 0.1s ~ 2.9s ).
		P1OUT	&=	~BIT0;								// LED1 OFF

		TA0CCR0 = 34800;		                		// TAIFG on around ~ 2.9 s
		TA0CTL  = TASSEL_1 + MC_1 + TACLR + TAIE;		// ACLK, upmode
		break;
	}
  }
}
