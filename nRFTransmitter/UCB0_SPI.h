/**
* @file		NRF24L01.h
* @author	Manuel Caballero
* @date 	4/2/2015
* @brief 	Variables/Constantes para el dispositivo NRF24L01.
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


// COMANDOS: Tipo de retardo necesarios para el dispositivo nRF24L01+
#define	RetardoLargo		0x01	/**< Reatrdo para Watchdog en configuración Timer. Retardo ~42.67 ms */
#define	RetardoSeguridad	0x02	/**< Reatrdo para Watchdog en configuración Timer. Retardo ~ 5.33 ms */
#define	RetardoCorto		0x02	/**< Reatrdo para Watchdog en configuración Timer. Retardo ~ 5.33 ms */


// Prototipo de funciones
uint8_t Write_Byte_UCB0_SPI (uint8_t );
void Delay_WDT ( uint16_t  );
