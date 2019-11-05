/**
* @file		funciones.c
* @author	Manuel Caballero
* @date 	4/2/2015
* @brief 	Funciones del sistema.
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
#include "funciones.h"


/**
 *  \brief     void conf_CLK (void)
 *  \details   Configura los relojes del MCU.
 *  				- Reloj Principal:  MCLK  = DCO      ~ 16 MHz.
 *  				- Reloj Secundario: SMCLK = MCLK/2   ~ 16 MHz.
 *  				- Reloj Auxiliar: 	ACLK  = VLOCLK   ~ 12 kHz.
 *  \author    Manuel Caballero
 *  \version   0.0
 *  \date      4/2/2015
 */
void conf_CLK (void)
{  
  DCOCTL    =   CALDCO_16MHZ;
  BCSCTL1   =   CALBC1_16MHZ;

  // BCSCTL2  |=	DIVS_1;				 // SMCLK = MCLK/2
  BCSCTL3   =   LFXT1S_2;            // ACLK = VLOCLK
}



/**
 *  \brief     void conf_WDT (void)
 *  \details   Desactiva el Watchdog del MCU.
 *  \author    Manuel Caballero
 *  \version   0.0
 *  \date      2/2/2015
 */
void conf_WDT (void)
{
  WDTCTL = WDTPW + WDTHOLD;     // Stop watchdog timer
}



/**
 *  \brief     void conf_IO (void)
 *  \details   Configura los pines del MCU a usar en este proyecto.
 *  				- Puerto 1: Módulo SPI.
 *  					- P1.0:	Salida.	  LED1     (Launchpad)
 *  					- P1.5: Salida.   UCB0CLK  (NRF24L01+)
 *  					- P1.6: Entrada.  UCB0SOMI (NRF24L01+)
 *  					- P1.7: Salida.   UCB0SIMO (NRF24L01+)
 *
 *  				- Puerto 2: Módulo SPI.
 *  					- P2.0: Salida.   CE   (NRF24L01+)
 *  					- P2.1: Salida.   CSN  (NRF24L01+)
 *  					- P2.2: Entrada.  #IRQ (NRF24L01+)
 *  \author    Manuel Caballero
 *  \version   0.0
 *  \date      4/2/2015
 */
void conf_IO (void)
{
  P1SEL  |=  BIT5 + BIT6 + BIT7;
  P1SEL2 |=  BIT5 + BIT6 + BIT7;

  P1DIR	 |=  BIT0;
  P2DIR	 |=	 BIT0 + BIT1;

  P1OUT  &=	~BIT0;						// LED1 OFF
  P2OUT	 |=	 BIT1 + BIT2;				// nRF24L01+ no seleccionado y IRQ = 1 ( activa en bajo )

  P2DIR  &= ~BIT2;
  P2OUT	 &=	~BIT0;						// nRF24L01+ desactivado
}



/**
 *  \brief     void conf_TimerA (void)
 *  \details   Configura el timer TA0 como Up Mode.
 *
 * 			   El TA0 será encargado de despertar al MCU del estado
 * 			   bajo consumo en, aproximadamente 3 s (36000/(~12kHz) ~ 3s).
 *
 * 	\pre	   El reloj ACLK debe estar a 12 kHz.
 *  \author    Manuel Caballero
 *  \version   0.0
 *  \date      2/2/2015
 */
void conf_TA0 (void)
{
  TA0CCR0 = 36000;		                	// TAIFG on around ~ 3s
  TA0CTL  = TASSEL_1 + MC_1 + TACLR + TAIE;	// ACLK, upmode, TA0 interrupt ON
}



/**
 *  \brief     void conf_SPI_B0 (void)
 *  \details   Configura USCI_B0 en modo SPI MAESTRO.
 *
 * 			   Configura el módulo USCI_B0 en modo SPI
 * 			   MAESTRO, f_USCI_B0 = f_(SMCLK/2), Síncrono.
 *
 * 	\pre	   El reloj SMCLK debe estar a 16 MHz.
 * 	\pre	   La frecuencia del SPI es SMCLK/2 = 16/2 = 8 MHz.
 *  \author    Manuel Caballero
 *  \version   0.0
 *  \date      4/2/2015
 */
void conf_SPI_B0 (void)
{
  UCB0CTL1 =   UCSWRST;
  UCB0CTL1 |=  UCSSEL_2 + UCSWRST;
  UCB0CTL0 |=  UCCKPH + UCMSB + UCMST + UCMODE_0 + UCSYNC;
  UCB0BR0  |=  0x02;                          					// SMCLK/2 = 16/2 ...
  UCB0BR1 	=  0;                              					// ... 8 MHz

  UCB0CTL1 &= ~UCSWRST;
}



/**
 *  \brief     void conf_ADC10 (void)
 *  \details   Configura ADC10 para la lectura del sensor interno de temperatura.
 *
 * 			   El módulo ADC10 será el encargado de hacer la lectura del sensor de
 *			   temperatura interno del uC. Según la hoja de características de esta familia
 *			   de microcontroladores, el documento: slau144j.pdf, la lectura binaria que
 *			   obtendremos en el registro ADC10MEM evndrá dada por la siguiente expresión:
 *
 *			     N_ADC = 1023·(V_IN - V_R-)/(V_R+ - V_R-)
 *
 *			   Teniendo en cuenta nuestra configuración: V_R+ = 2.5 V y V_R- = 0 V, tendremos
 *			   una lectura del sensor de tempertura tal y como se expresa a continuación:
 *
 *			     V_IN = N_ADC/409.2 = (5/2046)·N_ADC ~ N_ADC·0.002444
 *
 * 	\pre	   Voltajes de referencia:
 * 					· Vref+ = 2.5V
 * 					· Vref- = Vss.
 * 	\pre	   Hay que asegurarse que el tiempo de muestreo sea mayor a 30us:
 * 				    · Reloj interno: ADC10OSC/3 (~5/3:  ~ 1.67 MHz)
 * 				    · Tiempo muestreo en 64CLK: 64/(~5/3 MHz) ~ 38.4us -> Cumple la especificación.
 *  \author    Manuel Caballero
 *  \version   0.0
 *  \date      4/2/2015
 */
void conf_ADC10 (void)
{
  uint16_t degC = 0;

  ADC10CTL1 = INCH_10 + ADC10DIV_3;                                             // Temp Sensor y f_ADC10 ~ 5MHz/3
  ADC10CTL0 = SREF_1 + REFON + ADC10SHT_3 + REF2_5V + ADC10ON + ADC10IE;        // 64/(5MHz/3)

  for(degC = 30; degC > 0; degC-- );                              				// delay to allow reference to settle
}
