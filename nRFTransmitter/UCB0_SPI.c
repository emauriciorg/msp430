/**
* @file		UCB0_SPI.c
* @author	Manuel Caballero
* @date 	11/2/2015
* @brief 	Libreria para el módulo interno USCI_B0 en modo SPI.
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
#include "UCB0_SPI.h"


/**
 *  \brief     uint8_t Write_Byte_UCB0_SPI (uint8_t Byte)
 *  \details   Esta funcion manda un Byte por el módulo USCI_BO SPI.
 *
 *	@param 	   uint8_t Byte - Byte a enviar por el módulo SPI.
 *  @return	   aux
 *
 *  \author    Manuel Caballero
 *  \version   0.0
 *  \date      11/2/2015
 *  \pre       Esta función usa el Watchdog como Timer como tiempo de seguridad.
 *  \pre	   El reloj SMCLK debe ser de 8 Mhz.
 */

uint8_t Write_Byte_UCB0_SPI (uint8_t Byte)
{
	uint8_t aux = 0;

	Delay_WDT ( RetardoSeguridad );

	UCB0TXBUF   = 	 Byte;
	while ( !( IFG2 & UCB0RXIFG ) && !( IFG1 & WDTIFG ));		// USCI_B0 rX buffer ready?

	WDTCTL = WDTPW + WDTHOLD;     								// Stop watchdog timer

	aux			=	 UCB0RXBUF;

	return aux;
}


/**
 *  \brief     void Delay_WDT ( void )
 *  \details   Esta función provoca los retardos necesarios para el dispositivo nRF24L01+
 *  		   así como genera retardos de seguridad para evitar cuelgues del MCU.
 *
 *  \author    Manuel Caballero
 *  \version   0.0
 *  \date      16/2/2015
 *  \pre       El reloj del WDT debe estar asociado al ACLK = VLOCLK ( ~ 12 kHz ).
 */
void Delay_WDT ( uint16_t TipoRetardo )
{
	IFG1 &=	~WDTIFG;														// Reset flag

	if (TipoRetardo == RetardoLargo)
		WDTCTL = WDTPW + WDTTMSEL + WDTSSEL + WDTCNTCL + WDTIS1;			// Retardo Largo ~ 42.67 ms
	else
		WDTCTL = WDTPW + WDTTMSEL + WDTSSEL + WDTCNTCL + WDTIS0 + WDTIS1;	// Retardo Corto ~  5.33 ms (Retardo de seguridad)

	if ( TipoRetardo != RetardoSeguridad )
	{
		while ( !( IFG1 & WDTIFG ) );	// Wait until the delay is done

		WDTCTL = WDTPW + WDTHOLD;     	// Stop watchdog timer
	}
}
