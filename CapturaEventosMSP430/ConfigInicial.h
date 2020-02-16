/*
 * ConfigInicial.h
 *
 *  Created on: 6/11/2014
 *      Author: mauricio
 */

#ifndef CONFIGINICIAL_H_
#define CONFIGINICIAL_H_


#define div_1 0x0000
#define div_8 0x00c0
#define Adiv_4 0x0000 //0x0050  // 07 --0x00x3
#define Tdiv_4 0x0080
#define smclk 0x0200








void canal(unsigned int soyuncanal){
unsigned char ADCBITEN=0;
ADC10CTL0&=~0X0012;
switch(soyuncanal){
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


void Adc()
{
	ADC10CTL1 = INCH_5|ADC10DIV_0|ADC10SSEL_2;
	ADC10CTL0 = SREF_0 |/*ADC10SHT_0 |*/ ADC10ON | ADC10IE;
	ADC10AE0 |= 0XFF;
}

void inicioADC(){
	ADC10CTL0 |= (ENC | ADC10SC);
	}




void EnableInterrupts()
{
	_BIS_SR(GIE);
	__enable_interrupt();
	__bis_SR_register(GIE);
}



void configport1()
{
	P1DIR=0x41;
	P1SEL&=~0x41;
	P1SEL2&=~0x41;
	P1REN=0X00;
}

void configport2()
{

	P2DIR|=BIT5;
	P2SEL &=~(BIT3|BIT4|BIT5);
	P2SEL2 &=~(BIT3|BIT4|BIT5);

}


void ConfUart()
{
	P1SEL |=(BIT1 | BIT2);
    P1SEL2 |=(BIT1 | BIT2);

	UCA0CTL1 = UCSWRST;
	UCA0CTL1 |= 0x80;                     // SMCLK
	UCA0BR0 = 130;                            // 1MHz/ 9600 PREESCALAR
	UCA0BR1 = 6;                             //(UCAxBR0 + UCAxBR1 � 256)
	UCA0MCTL =0x00;//UCBRS0;                        // Modulation UCBRSx = 1
	UCA0CTL1 &= ~UCSWRST;
	IE2 |= UCA0RXIE;
}

void configclk()
{
	WDTCTL = WDTPW + WDTHOLD;                 // Stop WDT
	BCSCTL1 =CALBC1_16MHZ;
	BCSCTL2 =0x00;
	DCOCTL = CALDCO_16MHZ;
}


void port1interrupt()
{	P1DIR=0X41;
	//P1SEL=0X00;
//	P1SEL2=0X00;
	P1OUT=0X08;
	P1REN=0X08|0x41;
	P1IE=0X08; //Habilita la interrupcion asociada a P1IFG
	P1IFG=0X00; // set when a interrupt ocurrs
	P1IES=0X08; // INTERRUPT EDGE SELECT  EDGE SELECTS THE INTERRUPT EDGE FOR THE CORRESPONDIN I/O, 0 MEANS low-to-high transition, 1 means a high-to-low transition
}

void port2interrupt()
{	P2DIR=0X00;
	P2SEL=0X00;
	P2SEL2=0X00;
	P2OUT=0X00;
	P2REN=0X41;
	P2IE=0X06; //Habilita la interrupcion asociada a P1IFG
	P2IFG=0X00; // set when a interrupt ocurrs
	P2IES=0X0; // INTERRUPT EDGE SELECT  EDGE SELECTS THE INTERRUPT EDGE FOR THE CORRESPONDIN I/O, 0 MEANS low-to-high transition, 1 means a high-to-low transition
}

void configtimer(){

	CCR0=65534;
	TACCTL0=CCIE; //no capture mode+CCIA+Asynchronous en capture mode+modo comparacion+
	TACTL=ID_3|TASSEL_2|MC_1|TAIE;
}



void timer(unsigned int counts)
{
	TA1CCR1=1000;
	TA1CCTL1=OUTMOD_7; //no capture mode+CCIA+Asynchronous en capture mode+modo comparacion+
	TA1CTL=TASSEL_2|ID_3|MC_1|TAIE;
}

void external_events_init()
{
	P2DIR&=~(BIT1);
	P2SEL|=(BIT1);
	P2SEL2&=(~BIT1);
	P2REN=0X00;
	P2OUT=0X00;
	TA1CTL=ID_3|TASSEL_2|MC_2;
	//TA1CCTL0=CAP|CM_3|CCIE |SCS;
	TA1CCTL1=CAP|CM_1 |SCS;//|CCIS_1

/*
 *
 * 	TA1CTL=ID_3|TASSEL_2|MC_2|TAIE;
	//TA1CCTL0=CAP|CM_3|CCIE |SCS;
	TA1CCTL1=CAP|CM_1|CCIE |SCS;//|CCIS_1
 *
 *
 * */
}



void inicio()
{
	configclk();
	//configport1();
	//configport2();

	//port1interrupt();
    //port2interrupt();
	external_events_init();
	ConfUart();
	EnableInterrupts();
}


#endif /* CONFIGINICIAL_H_ */
