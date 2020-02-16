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
 *  \brief     void TA0_ISR(void) TimerA0 (TA0) interrupt service routine
 *  \details   Se despierta al MCU del estado de bajo consumo para indicarle
 *  		   que estado debe ejecutar:
 *
 *  		   		- opRESET:			Orden de realizar un reset al registro STATUS del nRF24L01+
 *  		   							( necesario cada vez que se env�a o recibe un paquete ).
 *
 *					- opuart_write_bytes:	Orden de enviar datos por el nRF24L01+.
 *
 *					- opCheckTx:		Orden de realizar una lectura al registro STATUS del nRF24L01+.
 *
 *					- opLED:			Orden de actuar sobre LED1 ( LED Rojo ).
 *
 *					- default:			Vuelta a empezar.
 *
 *			   El servicio de interrupci�n del TA0 estar� deshabilitado hasta
 *			   que se realice la orden prevista.
 *
 *			   Una vez completada la orden, se volver� a habilitar desde el programa principal ( main ).
 *
 *  \author    Manuel Caballero
 *  \version   0.0
 *  \date      2/2/2015
*/
#pragma vector=TIMER0_A1_VECTOR
__interrupt void TA0_ISR(void)
{
  TA0CTL   =  MC_0;   				// TimerA0 Stop mode
  TA0CTL  &= ~( TAIFG + TAIE );   	// Reset flag y Servicio de interrupci�n OFF

  switch ( OpFlow ){
  case opRESET:
  // Ya se ha realizado un RESET del registro STATUS del nRF24L01+, ahora podemos enviar datos.
	  OpFlow = opuart_write_bytes;
	  break;

  case opuart_write_bytes:
  // Ya se han enviado los datos, ahora vamos a leer el registro STATUS del nRF24L01+
	  OpFlow = opCheckTx;
	  break;

  case opCheckTx:
  // Ya se le�do el registro STATUS, ahora vamos a encender el LED Rojo o no ( seg�n la lectura del registro STATUS )
	  OpFlow = opLED;
	  break;

  case opLED:
  // Ya se ha actuado con el LED Rojo, ahora vamos a apagarlo para completar el parpadeo.
	  OpFlow = opTemInterna;
	  break;

  default:
  case opTemInterna:
  // Vuelta a empezar, se va a dar la orden de realizar una lectura del sensor de temperatura interno.
	  ADC10CTL0 |=  ENC + ADC10SC;   // Sampling and conversion start
	  OpFlow 	 =  opRESET;
	  break;
  }


  if ( OpFlow != opRESET )
	  LPM3_EXIT;                    // Clear CPUOFF bit from 0(SR)
}


/**
 *  \brief     void ADC10_ISR ADC10 interrupt service routine
 *  \details   Conversi�n de temperatura realizada.
 *
 *  		   Lectura del sensor interno de temperatura del uC que se
 *  		   almacena en la variable externa vector W_Buffer. Seg�n el datasheet
 *  		   de la familia en la que pertenece nuestro uC (slau144j.pdf), la
 *  		   expresi�n que describe al sensor de temperatura interno es
 *  		   la siguiente:
 *
 *  		      V_temp = 0.00355�(Temp_�C) + 0.986
 *
 *  		   Despejamos la variable que nos interesa (Temp_�C), para ello,
 *  		   se recomienda las siguientes recomendaciones:
 *
 *  		     � Trabajar en mV.
 *  		     � Redondear a n�meros enteros.
 *
 *  		   Una vez dispuesto lo anterior, tenemos la siguiente expresi�n:
 *
 *  		      Temp_�C = ((V_temp - 672)*423)/1023;
 *
 *  		   El tiempo total de muestreo y conversi�n viene dada por la
 *  		   siguiente expresi�n:
 *
 *  		       t_sample&conversion = t_sync + t_sample + t_convert
 *
 *  		   Donde, en nuestro caso:
 *
 *  		      � t_sync:     1 x ADC10CLK (Siempre es este valor)
 *  		      � t_sample:   64 x ADC10CLKs
 *  		      � t_convert:  13 x ADC10CLKs
 *  		      � t_total:    (1 + 64 + 13) x ADC10CLKs = 78 x ADC10CLKs
 *
 *  		   Nuestro reloj es: ~5/3 ~ 1.67MHz
 *
 *  		   Por lo tanto, el tiempo total consumido ser�:
 *
 *  		      � t_total:   78 x ADC10CLKs = 78/(5/3 MHz) ~ 46.8us
 *
 *  \author    Manuel Caballero
 *  \version   0.0
 *  \date      19/2/2015
 */

#pragma vector=ADC10_VECTOR
__interrupt void ADC10_ISR (void)
{
  W_Buffer [ 0 ] =	ADC10MEM;           // (parte baja) del dato del sensor de temperatura.
  W_Buffer [ 1 ] =	( ADC10MEM >> 8 );	// Los 2-bits (parte alta) del dato del sensor de temperatura que quedan.


  ADC10CTL0 &= ~ENC;            		// ADC10 OFF

  LPM3_EXIT;							// Clear CPUOFF bit from 0(SR)
}
