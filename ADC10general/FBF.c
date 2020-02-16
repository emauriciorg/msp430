/*
 * FBF.h
 *
 *  Created on: 28/01/2015
 *      Author: Mauricio Rios
 *
 *
 *
 *
 *      The FBF is and abreviation for FuntionalBlockFunctions, this header file contain almost all
 *      the software necessary for drive the Msp430's Funtional Block, every drive is set on interrupt mode.
 *
 *      Blocks included:
 *      I/O interrupts,pull-up/down resistor,
 *      Analog almost all channels with a single reading or multi-reading
 *      Timer0 and Timer3
 *      pwm,capture/compare
 *      uart_init
 *      i2c master mode
 *
 */


void ADC10f()
{
	ADC10CTL1 	 = 		INCH_7|ADC10DIV_4|CONSEQ_2	;           // CHANEL INPUT AND MODE
	ADC10CTL0 	 = 		ADC10SHT_3|ADC10SR|REFBURST|MSC|REF2_5V|REFON | ADC10ON | ADC10IE;  // REFERENCE AND TIMING
	ADC10AE0 	|= 		BIT7;                        //ENABLE THE ANALOG CHANNEL ADC option�
}

void initADC10()
{
	ADC10CTL0	|=		(ENC|ADC10SC ) ;
}

void I2CReceiver()
{


	P1SEL       |=    	BIT6 + BIT7;                     // Assign I2C pins to USCI_B0
	P1SEL2      |= 	    BIT6 + BIT7;                     // Assign I2C pins to USCI_B0
	UCB0CTL1    |= 		UCSWRST;                      // Enable SW reset
	UCB0CTL0     = 		UCMODE_3 + UCSYNC;             // I2C Slave, synchronous mode
	UCB0I2COA    = 		0x48;                         // Own Address is 048h
	UCB0CTL1    &= 		~UCSWRST;                     // Clear SW reset, resume operation
	IE2 		|= 		UCB0RXIE;                          // Enable RX interrupt

}


void I2Ctransmitter(){

	  P1SEL |= BIT6 + BIT7;                     // Assign I2C pins to USCI_B0
	  P1SEL2|= BIT6 + BIT7;                     // Assign I2C pins to USCI_B0
	  UCB0CTL1 |= UCSWRST;                      // Enable SW reset
	  UCB0CTL0 = UCMST + UCMODE_3 + UCSYNC;     // I2C Master, synchronous mode
	  UCB0CTL1 = UCSSEL_2 + UCSWRST;            // Use SMCLK, keep SW reset
	  UCB0BR0 = 12;                             // fSCL = SMCLK/12 = ~100kHz
	  UCB0BR1 = 0;
	  UCB0I2CSA = 0x48;                         // Slave Address is 048h
	  UCB0CTL1 &= ~UCSWRST;                     // Clear SW reset, resume operation
	  IE2 |= UCB0TXIE;                          // Enable TX interrupt
	//  TXData = 0x00;                            // Holds TX data
}

void enable_interrupts()
{
	_BIS_SR(GIE);
	__enable_interrupt();
	__bis_SR_register(GIE);
}



void configport()
{
	P1DIR|=0X40;
	P1OUT=0X00;


	P2DIR=0XFF;
	P2SEL =0X00;
	P2SEL2 =0X00;
	P2OUT=0X00;
	P2REN=0X0000;
}

void uart_init()
{
	P1SEL |= (BIT1 | BIT2);
	P1SEL2 |= (BIT1 | BIT2);
	UCA0CTL1 = UCSWRST;
	UCA0CTL1 |= 0x80;                     // SMCLK
	UCA0BR0 = 130;                            // 16MHz 9600 PREESCALAR
	UCA0BR1 = 6;                             //(UCAxBR0 + UCAxBR1 � 256)
	UCA0MCTL =0x0c;//UCBRS0;                        // Modulation UCBRSx = 1
	UCA0CTL1 &= ~UCSWRST;
	IE2 |= UCA0RXIE;
}

void clk_init()
{
	WDTCTL = WDTPW | WDTHOLD;                 // Stop WDT
	BCSCTL1 =CALBC1_16MHZ;
	BCSCTL2 =0x00;
	DCOCTL = CALDCO_16MHZ;
}




void interrupcion()
{
	P2IE=0X03; //Habilita la interrupcion asociada a P1IFG
	P2IFG=0X00; // set when a interrupt ocurrs
	P2IES=0X0000; // INTERRUPT EDGE SELECT  EDGE SELECTS THE INTERRUPT EDGE FOR THE CORRESPONDIN I/O, 0 MEANS low-to-high transition, 1 means a high-to-low transition
}



void external_events_init(){
// this function recieve the input in rising/fall/both edges and store the count when it happend and when it ends, after that it gives to you a to values of
//	count event one and event two it is on p2.0 pin which is the cci1 from timer3, this pin is on pull-down resistor.see times and etc.

	P2OUT=0X00;
	P2DIR&=(~0X01);
	P2SEL|=0X01;
	P2SEL2&=(~0X01);
	P2REN=0X00;
	TA1CTL=ID_3|TASSEL_2|MC_2;
	TA1CCTL0=CAP|CM_3|CCIE|SCS;
}

void timer0(){
	TA0CCR0=60000;
	TACCTL0=CCIE; //no capture mode+CCIA+Asynchronous en capture mode+modo comparacion+
	TACTL=ID_3|TASSEL_2|MC_1|TAIE;
}

void configtimer3(){
	TA1CCR0=20000;
	TA1CCTL0=CCIE; //no capture mode+CCIA+Asynchronous en capture mode+modo comparacion+
	TA1CTL=ID_3|TASSEL_2|MC_1|TAIE;
}
