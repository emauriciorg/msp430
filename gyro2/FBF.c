#include "FBF.h"

void timer0(void)
{
	TA0CCR0=8000;
	TACCTL0=CCIE; //no capture mode+CCIA+Asynchronous en capture mode+modo comparacion+
	TACTL=TASSEL_2|MC_1|TAIE;//ID_3|
}


void canal(unsigned int soyuncanal)
{
	unsigned char ADCBITEN=0;
	ADC10CTL0&=~0X0012;
	switch(soyuncanal)
	{

		case 0: ADCBITEN=0X01;break;
		case 1:ADCBITEN=0X02;break;
		case 2:ADCBITEN=0X04;break;
		case 3:ADCBITEN=0X08;break;
		case 4:ADCBITEN=0X10;break;
		case 5:ADCBITEN=0X20;break;
		case 6:ADCBITEN=0X40;break;
		case 7:ADCBITEN=0X80;break;

		default:  ADCBITEN=0X00;  break;
	}
	ADC10CTL1 =(soyuncanal<<12) |ADC10DIV_0|ADC10SSEL_2;
	ADC10CTL0 = SREF_0  | ADC10ON | ADC10IE;
	ADC10AE0 = ADCBITEN;
}


void Adc(void)
{
	ADC10CTL1 =INCH_5|ADC10SSEL_2 	|ADC10DIV_7; //  |CONSEQ_3Channel 5, ADC10CLK/4
	ADC10CTL0 = ADC10SHT_3|MSC|ADC10IE|ADC10ON|ADC10SR|REFBURST;
	ADC10AE0 |= 0x0038;                        //P1.5 ADC option�
}

void inicioADC(void){
	ADC10CTL0 |= (ENC | ADC10SC);
}




void Enableinterrupts(void)
{
	_BIS_SR(GIE);
	__enable_interrupt();
	__bis_SR_register(GIE);
}

void digitalio(void)//put receiver variable like pull-up, in/out port name
{
	P1DIR|=(BIT3|BIT2);
	P1SEL&=~(BIT3|BIT2);
	P1SEL2&=~(BIT3|BIT2);
	P1REN=0X00;

	   P2DIR=0XFF;
		P2SEL =0X00;
		P2SEL2 =0X00;
		P2OUT=0X00;
		P2REN=0X00;

}


void configport1(void)
{
	P1DIR=0x41;
	P1SEL&=~0x41;
	P1SEL2&=~0x41;
	P1REN=0X00;
}




void configport2(void)
{

	P2DIR=0X00;
	P2SEL =0X00;
	P2SEL2 =0X00;
	P2OUT=0X01;
	P2REN=0X01;
}


void uart_init(void)
{
	P1SEL |=(BIT1 | BIT2);
	P1SEL2 |=(BIT1 | BIT2);

	UCA0CTL1 = UCSWRST;
	UCA0CTL1 |= UCSSEL_2;                     // SMCLK
	UCA0BR0 = 208;//130;                            // 16MHz 9600 PREESCALAR
	UCA0BR1 = 0;//6;                             //(UCAxBR0 + UCAxBR1 � 256)
	UCA0MCTL =0X00;//0x0c;//UCBRS0;                        // Modulation UCBRSx = 1
	UCA0CTL1 &= ~UCSWRST;
	IE2 |= 0;//UCA0TXIE;
}

void clk_init(void)
{
	WDTCTL = WDTPW + WDTHOLD;                 // Stop WDT
	BCSCTL1 =CALBC1_16MHZ;
	BCSCTL2 =DIVS_3;
	DCOCTL = CALDCO_16MHZ;

}


void port1interrupt(void)
{
	P1DIR=0X41;
	P1OUT=0X08;
	P1REN=0X08|0x41;
	P1IE=0X08; //Habilita la interrupcion asociada a P1IFG
	P1IFG=0X00; // set when a interrupt ocurrs
	P1IES=0X08; // INTERRUPT EDGE SELECT  EDGE SELECTS THE INTERRUPT EDGE FOR THE CORRESPONDIN I/O, 0 MEANS low-to-high transition, 1 means a high-to-low transition
}

void port2interrupt(void)
{
	P2DIR=0X00;
	P2SEL=0X00;
	P2SEL2=0X00;
	P2OUT=0X00;
	P2REN=0X41;
	P2IE=0X06; //Habilita la interrupcion asociada a P1IFG
	P2IFG=0X00; // set when a interrupt ocurrs
	P2IES=0X0; // INTERRUPT EDGE SELECT  EDGE SELECTS THE INTERRUPT EDGE FOR THE CORRESPONDIN I/O, 0 MEANS low-to-high transition, 1 means a high-to-low transition
}

void eventosexternos(void)
{

	P1OUT=0X00;
	P2OUT=0X00;
	P2DIR&=(~0X01);
	P2SEL|=0X01;
	P2SEL2&=(~0X01);
	P2REN=0X00;

	TA1CTL=ID_3|TASSEL_2|MC_2;
	TA1CCTL0=CAP|CM_3|CCIE|SCS;
}


void i2cmaster(void)
{

	P1OUT &= ~BIT0;                           // P1.0 = 0
	P1DIR |= BIT0;                            // P1.0 output
	P1SEL |= BIT6 + BIT7;                     // Assign I2C pins to USCI_B0
	P1SEL2|= BIT6 + BIT7;                     // Assign I2C pins to USCI_B0
	UCB0CTL1 |= UCSWRST;                      // Enable SW reset
	UCB0CTL0 = UCMST + UCMODE_3 + UCSYNC;     // I2C Master, synchronous mode
	UCB0CTL1 = UCSSEL_2 + UCSWRST;            // Use SMCLK, keep SW reset
	UCB0BR0 = 12;                             // fSCL = SMCLK/12 = ~100kHz
	UCB0BR1 = 0;
	UCB0I2COA = 0;                         // Own Address is 048h
	UCB0	I2CSA =0x6B;//0XD7>>1;// SADHR>>1; SLAVE DIRECTION
	UCB0CTL1 &= ~UCSWRST;                     // Clear SW reset, resume operation
	IE2=0;
}


void inicio()
{
	clk_init();
	Adc();
	digitalio();
	uart_init();
	timer0();
}
