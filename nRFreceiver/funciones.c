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
 *  				- Puerto 1: Módulo SPI, LED1 y módulo UART.
 *  					- P1.0:	Salida.	  LED1     (Launchpad)
 *  					- P1.2: Salida.   Tx 	   (Launchpad)
 *  					- P1.5: Salida.   UCB0CLK  (NRF24L01+)
 *  					- P1.6: Entrada.  UCB0SOMI (NRF24L01+)
 *  					- P1.7: Salida.   UCB0SIMO (NRF24L01+)
 *
 *  				- Puerto 2: Módulo SPI.
 *  					- P2.0: Salida.   CE   (NRF24L01+)
 *  					- P2.1: Salida.   CSN  (NRF24L01+)
 *  					- P2.2: Entrada.  #IRQ (NRF24L01+). Produce interrupción
 *  \author    Manuel Caballero
 *  \version   0.0
 *  \date      17/2/2015
 */
void conf_IO (void)
{
  P1SEL  |=  BIT2 + BIT5 + BIT6 + BIT7;
  P1SEL2 |=  BIT2 + BIT5 + BIT6 + BIT7;

  P1DIR	 |=  BIT0;
  P2DIR	 |=	 BIT0 + BIT1;

  P1OUT  &=	~BIT0;						// LED1 OFF
  P2OUT	 |=	 BIT1 + BIT2;				// nRF24L01+ no seleccionado y #IRQ = 1 ( activa en bajo )

  P2DIR  &= ~BIT2;
  P2OUT	 &=	~BIT0;						// nRF24L01+ desactivado

  P2IES  |=  BIT2;        				// P2.2 Hi/lo edge
  P2IFG  &= ~BIT2;       				// P2.2 IFG cleared
  P2IE   |=  BIT2;         				// P2.2 interrupt enabled
}



/**
 *  \brief     void conf_UART (void)
 *  \details   Configura el módulo UART a 115200 Baud Rate.
 *
 * 		· Reloj UART: SMCLK ~ 16 MHz.
 * 		· Buad Rate ~ 115200:
 *
 *     		N = f_BRCLK/BaudRate = 16MHz/115200 ~ 138.89 = {Parte entera} = 138
 *
 *      	N >= 16 -->  Oversampling ON (UCOS16 = 1)
 *
 * 		Por lo tanto:
 *
 *     		UCBRx = INT(N/16) = INT(138/16) = 8
 *     		UCBRFx = ROUND[((N/16) - INT(N/16))·16] = ROUND[((16MHz/115200)/16 - INT((16MHz/115200)/16))·16] ~ 10.89 = 11
 *
 * 		· Activamos UART
 * 	\pre	   Para ampliar información: Documentos slau144j.pdf, apartado 15 Universal Serial Comunication
 *			   se pueden encontrar datos tabulados a distintas frecuencias.
 * 	\pre	   El reloj SMCLK debe estar a 16 MHz.
 *  \author    Manuel Caballero
 *  \version   0.0
 *  \date      17/2/2015
 */
void conf_UART (void)
{
  UCA0CTL1 |=  UCSSEL_2;                // SMCLK ~ 16MHz
  UCA0BR0   =  8;                       // 16MHz 115200 (Oversampling)
  UCA0BR1   =  0;                       // 16MHz 115200 (Oversampling)

  UCA0MCTL  =  UCBRF_11 + UCOS16;       // Modulation UCBRFx = 11 y Oversampling ON
  UCA0CTL1 &= ~UCSWRST;                 // **Initialize USCI state machine**
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
