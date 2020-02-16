/**
* @file		interrupciones.h
* @author	Manuel Caballero
* @date 	2/2/2015
* @brief 	Variables de las rutinas de interrupci�n.
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

#define opTemInterna	0			/**<  Estado opTemInterna: 	Petici�n de lectura del sensor interno de temperatura  */
#define opRESET			1			/**<  Estado RESET: 		realiza un RESET al dispositivo nRF24L01+  */
#define	opuart_write_bytes	2			/**<  Estado Enviar Datos: 	envia paquete por el dispositivo nRF24L01+  */
#define	opCheckTx		3			/**<  Estado CheckTx: 		comprueba que la transmisi�n ha sido satisfactoria  */
#define	opLED			4			/**<  Estado LED: 			Cambia el estado del LED1  */


// Prototipo de subrutina de interrupci�n


// Variable externa
extern volatile uint16_t OpFlow;
extern uint8_t W_Buffer [2];
