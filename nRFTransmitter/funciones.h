/**
* @file		funciones.h
* @author	Manuel Caballero
* @date 	2/2/2015
* @brief 	Prototipo de funciones.
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


// Prototipo de funciones
void conf_CLK           (void);
void conf_WDT           (void);
void conf_IO            (void);
void conf_SPI_B0        (void);
void conf_TA0			(void);
void conf_ADC10			(void);
