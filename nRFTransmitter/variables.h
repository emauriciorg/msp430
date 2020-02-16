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

#define opTemInterna	0			/**<  Estado opTemInterna: 	Petici�n de lectura del sensor interno de temperatura  */
#define opRESET			1			/**<  Estado RESET: 		realiza un RESET al dispositivo nRF24L01+  */
#define	opuart_write_bytes	2			/**<  Estado Enviar Datos: 	envia paquete por el dispositivo nRF24L01+  */
#define	opCheckTx		3			/**<  Estado CheckTx: 		comprueba que la transmisi�n ha sido satisfactoria  */
#define	opLED			4			/**<  Estado LED: 			Cambia el estado del LED1  */


#define	ERROR			0xFF		/**<  Comando ERROR: 		ha habido un error en la transmisi�n  */
#define	RESET			0x00		/**<  Comando RESET: 		realiza un reset a la variable  */

/**
 *  \brief     Variables Globales
 *  \details
 * 				- OpFlow:		Dicha variable se emplea conjutamente en el servicio de interrupci�n
 *                  	 		del TimerA TA0, para indicar que acci�n a realizar:
 *
 *                  	 			- OpFlow = opuart_write_bytes:	Se env�a datos mediante nRF24L01+.
 *                  	 			- OpFlow = opCheckTX:		Se compreba que se ha realizado la transmisi�n.
 *                  	 			- OpFlow = opLED:			Se enciende LED si se ha transmitido o no.
 *
 *                  	 											� Parpadeo LED Rojo: 		Tx perfecta ( ACK recibido tambi�n ).
 *                  	 											� NO Parpadeo LED Rojo:  	Tx fallo ( o no se ha enviado o ACK no recibido ).
 *
 *								Se inicializa en el estado de opTemInterna ( OpFlow = 0 ).
 */
volatile uint16_t OpFlow = 0;


/**
 *  \brief     Variables Globales
 *  \details
 * 				- W_Buffer [2]:		Variable vector, dedicada a recoger el valor de la temperatura interna.
 */
uint8_t W_Buffer [2] = {0};
