/**
* @file		NRF24L01.c
* @author	Manuel Caballero
* @date 	11/2/2015
* @brief 	Libreria para el dispositivo nRF24L01+.
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
#include "NRF24L01.h"



/**
 *  \brief     uint16_t *nRF24L01_WriteRead (uint16_t , uint16_t , uint8_t *, uint16_t )
 *  \details   Esta funcion realiza tanto la lectura como escritura en el dispositivo nRF24L01+.
 *
 *	@param 	   uint16_t WriteRead - Dictaminamos si vamos a leer o escribir un comando empleando
 *									los siguientes comandos: R_REGISTER (lectura) o W_REGISTER (escritura).
 *	@param 	   uint16_t reg 	  - Registro que se desea actuar.
 *  @param     uint8_t *val 	  -	Modo escritura, esta variable contiene los elementos a escribir
 *  								en el registro seleccionado.
 *  @param     uint16_t len 	  -	Cantidad de Bytes a enviar o escribir en el registro seleccionado.
 *  @return	   ret
 *
 *  \author    Manuel Caballero
 *  \version   0.0
 *  \date      11/2/2015
 *  \pre       Asegurarse de las conexiones del dispositivo nRF24L01+.
 *  \pre	   Esta función usa el módulo UCB0 en modo SPI.
 */
uint8_t *nRF24L01_WriteRead (uint16_t WriteRead, uint16_t reg, uint8_t *val, uint16_t len)
{
	static uint8_t ret [ 32 ] = {0};
	uint16_t i	= 0;


	if ( WriteRead == W_REGISTER )
	{
		reg = W_REGISTER + reg;
	}

	P2OUT		&=	~BIT1;
	Write_Byte_UCB0_SPI ( reg );

	for ( i = 0; i < len ; i++ )
	{
		if ( ( WriteRead == R_REGISTER ) && ( reg != W_TX_PAYLOAD ) )
			ret [ i ] = Write_Byte_UCB0_SPI ( NOP );
		else
			Write_Byte_UCB0_SPI ( val [ i ] );
	}

	P2OUT		|=	 BIT1;


	return ret;
}


/**
 *  \brief     void nRF24L01_init ( void )
 *  \details   Esta funcion inicializa el dispositivo nRF24L01+.
 *
 *  \author    Manuel Caballero
 *  \version   0.0
 *  \date      11/2/2015
 *  \pre       Esta función utiliza el Watchdog como Timer, tanto para retardos como para tiempo de seguridad.
 *  \pre	   La configuración es la siguiente:
 *  				- AUTO ACK Activado.
 *  				- Pipe ERX_P0 Activada.
 *  				- 5-Bytes de tamaño de dirección ( RF_Address ).
 *  				- Canal 1 Activado.
 *  				- Velocidad 1Mbps, potencia 0dBm.
 *  				- Dirección del RECEPTOR: 	0x12.
 *  				- Dirección del TRANSMISOR: 0x12.
 *  				- Tamaño de envío ( Payload ): 2-Byte.
 *  				- AUTO Re-transmión: cada 750us SOLO una re-transmisión.
 *  				  Note: ¡Cuidado! En caso de que no se pueda enviar un dato, tal y como está
 *  				  configurado la AUTO Re-transmisión, intentará reenviar el dato una vez más,
 *  				  por lo que tardará: 750us + 750us = 1.5ms.
 *
 *  				  Este tiempo debe ser inferior al tiempo de seguridad utilizado el la función
 *  				  uint16_t nRF24L01_send ( uint8_t * ), que emplea el Watchdog ( en este caso,
 *  				  el tiempo de seguridad es de aproximadamente 5.33ms ).
 *
 *  				  En caso de que no se cumpla, podemos tener una errónea lectura del registro
 *  				  STATUS del nRF24L01+ para comprobar los flags.
 *
 *  				- nRF24L01+ Modo TRANSMISOR, POWER UP ( nRF24L01+ estado Standby-I ).
 *
 *	\pre		En caso de cambiar la configuración expuesta, se deberá actuar dentro de esta función.
 *	\pre		Según en la Figura 3. Radio control state diagram ( datasheet nRF24L01+ ), los tiempos
 *				de espera son menores de los que esta función presenta, eso es así ya que se ha utilizado
 *				el Watchdog como Timer para generar dichos retardos, y no es preciso. En caso de ajustar
 *				dichos tiempos, se recomienda el uso de uno de los Timers del microcontrolador donde se
 *				pueda configurar el tiempo que se desea.
 */
void nRF24L01_init ( void )
{
	uint8_t val [ 5 ] = {0};
	uint16_t i	= 0;

	Delay_WDT ( RetardoLargo );		// Power on Reset ~ 42.67 ms ( Datasheet says >= 10.3 ms )


	// Enable AUTO ACK
	// NOTE:	RX addres for data pipe 0 (RX_ADDR_P0) has to be equal to the TX address (TX_ADDR) in the PTX device
	val [ 0 ]	= ENAA_P0;
	nRF24L01_WriteRead (W_REGISTER, EN_AA, val, 1);

	// Number of enabled data pipes ( 1 - 5 )
	val [ 0 ]	= ERX_P0;
	nRF24L01_WriteRead (W_REGISTER, EN_RXADDR, val, 1);

	// RF_Address width setup (how many bytes is the receiver)
	val [ 0 ]	= 0x03;										// 5 Bytes RF_Address
	nRF24L01_WriteRead (W_REGISTER, SETUP_AW, val, 1);

	// RF channel setup (frequency 2,400 - 2,527 GHz, 1 MHz/step)
	val [ 0 ]	= 0x01;										// 2,401 GHz (same on TX and RX)
	nRF24L01_WriteRead (W_REGISTER, RF_CH, val, 1);

	// RF setup (power mode and data speed)
	val [ 0 ]	= 0x07;										// 1Mbps, 0dBm
	nRF24L01_WriteRead (W_REGISTER, RF_SETUP, val, 1);

	// RECEIVER RX: RF Address setup 5 Bytes (set RX_ADDR_P0 = TX_ADDR if EN_AA is ENABLED !!!)
	for ( i = 0; i < 5; i++ )
		val [ i ] = 0x12;		// RX address: 0x12

	nRF24L01_WriteRead (W_REGISTER, RX_ADDR_P0, val, 5);	// Pipe 0 because of it was the selected channel
	// Here we can give different addresses to different channels ( if they are enabled in EN_RXADDR ) to listen on several different transmitters


	// TRANSMITTER TX: RF Address setup 5 Bytes (set RX_ADDR_P0 = TX_ADDR if EN_AA is ENABLED !!!)
	for ( i = 0; i < 5; i++ )
		val [ i ] = 0x12;		// TX address: 0x12

	nRF24L01_WriteRead (W_REGISTER, TX_ADDR, val, 5);


	// PAYLOAD width setup ( 1 - 32 byte)
	val [ 0 ]	= 0x02;										// 2-Byte per package
	nRF24L01_WriteRead (W_REGISTER, RX_PW_P0, val, 1);


	// Setup of Automatic Retransmission
	val [ 0 ]	= 0x21;										// 750us delay between every retry (at least 500us at 250kbps and if payload > 5bytes in 1Mbps
															// and if pauload >15bytes in 2Mbps). 1 retries.
	nRF24L01_WriteRead (W_REGISTER, SETUP_RETR, val, 1);


	// CONFIG setup
	val [ 0 ]	= 0x1E;										// Transmitter, Power Up and IRQ-interrupt NOT triggered if transmission failed
	nRF24L01_WriteRead (W_REGISTER, CONFIG, val, 1);

	Delay_WDT ( RetardoCorto );								// Start Up ~ 5.33 ms ( Datasheet says >= 1.5 ms )

	// El dispositivo nEF24L01+ se encuentra configurado y en modo Standby-I
}



/**
 *  \brief     uint8_t nRF24L01_send ( uint8_t *, uint16_t )
 *  \details   Esta funcion envía datos por dispositivo nRF24L01+, antes realiza un vaciado
 *  		   del Buffer del dispositivo nRF24L01+ para posteriormente cargar los datos a enviar.
 *
 *  @param     uint8_t  *Buffer 	  -	Vector que contiene los datos a enviar.
 *  @param     uint16_t len 	 	  -	Cantidad de datos a enviar.
 *  @return	   Esta función devuelve lo siguiente:
 *
 *  				- 0x0000:	Transmisión correcta.
 *  				- 0xFFFF:	Transmisión fallida.
 *
 *  \author    Manuel Caballero
 *  \version   0.0
 *  \date      11/2/2015
 *  \pre       Esta función emplea el Watchdog como Timer para tiempo de seguridad.
 *  		   Note: ¡Cuidado! Prestar atención a como está configurado la AUTO Re-transmisión,
 *  		   cuanto tiempo tarda dicha tarea, ya que debe ser menor al tiempo de seguridad.
 *  \pre	   Esta función usa el pin #IRQ del nRF24L01+ conectado a P2.2 del microcontrolador.
 *  \pre	   La comprobación de que se ha enviado los datos es mediante polling, en caso de querer
 *  		   usarse la interrupción, se deberá modificar esta función.
 */
uint8_t nRF24L01_send ( uint8_t *Buffer, uint16_t len )
{
	nRF24L01_WriteRead (R_REGISTER, FLUSH_TX, Buffer, 0);
	nRF24L01_WriteRead (R_REGISTER, W_TX_PAYLOAD, Buffer, len);


	P2OUT	|=	 BIT0;											// Start transmission

	Delay_WDT ( RetardoSeguridad );
	while ( (P2IN & BIT2) == BIT2  && !( IFG1 & WDTIFG ) );		// Wait until the package is sent or TimeOut
	WDTCTL = WDTPW + WDTHOLD;     								// Stop watchdog timer

	P2OUT	&=	~BIT0;											// nRF24L01+ mode: Standby-I

	if ( !( IFG1 & WDTIFG ) )
	{
	// Transmisión correcta
		return 0x00;
	}
	else
	{
	// Ha habido un error en la transmisión
		return 0xFF;
	}
}


/**
 *  \brief     void nRF24L01_reset ( void )
 *  \details   Esta función realiza un reset a los flags del registro STATUS. Es necesario realizar
 *  		   dicho reset, cada vez que se envíe o reciba un paquete.
 *
 *  \author    Manuel Caballero
 *  \version   0.0
 *  \date      11/2/2015
 */
void nRF24L01_reset ( void )
{
	uint8_t val [ 1 ] = {0x70};

	nRF24L01_WriteRead (W_REGISTER, STATUS, val, 1);
}
