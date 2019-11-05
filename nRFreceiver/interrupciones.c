/**
* @file		interrupciones.c
* @author	Manuel Caballero
* @date 	2/2/2015
* @brief 	Interrupciones del sistema.
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
#include "interrupciones.h"


/**
 *  \brief     void USCI0TX_ISR(void) UART Tx interrupt service routine
 *  \details   Se transmite por la UART los datos recibidos por el dispositivo nRF24L01+.
 *
 *  		   La variable global TX_Buff actúa de cuantos datos se van a enviar.
 *
 *			   Una vez transmitidos todos los datos, se desactiva la transmisión y
 *			   se vuelve a activar el servicio de interrupción P2.2.
 *
 *  \author    Manuel Caballero
 *  \version   0.0
 *  \date      19/2/2015
 */
#pragma vector=USCIAB0TX_VECTOR
__interrupt void USCI0TX_ISR(void)
{
  if (TX_Buff < 3)							// Solo trasnmite 3-Bytes
  {
    UCA0TXBUF  =  *pBuff;    				// Transmite 1-Byte

    TX_Buff++;
    pBuff++;
  }
  else
  {
  // Se han transmitido todos los datos
    IE2     &= ~UCA0TXIE;    // Interrupción Tx OFF (Desactiva transmisión de datos)
    TX_Buff  =	0;			 // Reset TX_Buff;
    P2OUT	|=  BIT0;		 // nRF24L01+ activado ( CE HIGH )
    P2IE    |=  BIT2;		 // Restore P2.2 interrupt enabled
    P1OUT	&= ~BIT0;	 	 // LED1 OFF
  }
}


/**
 *  \brief     void P2_ISR(void) PORT 2 interrupt service routine
 *  \details   Cada vez que se recive un dato por el dispositivo nRF24L01+, pone en
 *  		   señal baja su pin #IRQ, provocando una interrupción en el
 *  		   microcontrolador.
 *
 *  		   Esta acción, despierta al microcontrolador del modo bajo consumo
 *  		   para empezar a realizar las tareas asignadas.
 *
 *			   La interrupción del pin P2.2 se desactiva y se volverá a activar
 *			   una vez se transmitan todos los datos por la UART.
 *
 *  \author    Manuel Caballero
 *  \version   0.0
 *  \date      14/2/2015
 */
#pragma vector=PORT2_VECTOR
__interrupt  void P2_ISR(void)
{
	P2IE  &= ~BIT2;		  // P2.2 interrupt OFF
	P2IFG &= ~BIT2;       // P2.2 IFG cleared

	LPM4_EXIT;            // Clear CPUOFF bit from 0(SR)
}
