/**
* @file		variables.h
* @author	Manuel Caballero
* @date 	2/2/2015
* @brief 	Variables del sistema.
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

/**
 *  \brief     Variables Globales
 *  \details
 * 				- TX_Buff:		Dicha variable se emplea conjutamente en el servicio de interrupción
 *                  	 		de la transmisión de datos UART, para indicar el número de Bytes a
 *                  			enviar.
 */


/**
 *  \brief     Variables Globales
 *  \details
 *  			- *pBuff:		Puntero encargado de almacenar los datos leídos por el dispositivo
 *  							externo nRF24L01+. Se emplea conjuntamente con el servicio de
 *  							interrupción de la transmisión de datos UART para enviar su contenido.
 */
volatile uint8_t	*pBuff;
