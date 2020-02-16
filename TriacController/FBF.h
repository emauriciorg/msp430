	/*
	 * FBF.h
	 *
	 *  Created on: 6/11/2014
	 *      Author: mauricio
	 */

	#ifndef FBF_H_
	#define FBF_H_



	void timer0()
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


	void Adc()
	{
		ADC10CTL1 =INCH_5|ADC10SSEL_2 	|ADC10DIV_7; //  |CONSEQ_3Channel 5, ADC10CLK/4
		ADC10CTL0 = ADC10SHT_3|MSC|ADC10IE|ADC10ON|ADC10SR|REFBURST;
		ADC10AE0 |= 0x0038;                        //P1.5 ADC option�
	}

	void inicioADC(){
		ADC10CTL0 |= (ENC | ADC10SC);
		}




	void Enableinterrupts()
	{
		_BIS_SR(GIE);
		__enable_interrupt();
		__bis_SR_register(GIE);
	}

	void digitalio()//put receiver variable like pull-up, in/out port name
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


	void configport1()
	{
		P1DIR=0x41;
		P1SEL&=~0x41;
		P1SEL2&=~0x41;
		P1REN=0X00;
	}




	void configport2()
	{

		P2DIR=0X00;
		P2SEL =0X00;
		P2SEL2 =0X00;
		P2OUT=0X01;
		P2REN=0X01;
	}


	void uart_init()
	{
		P1SEL |=(BIT1 | BIT2);
		P1SEL2 |=(BIT1 | BIT2);

		UCA0CTL1 = UCSWRST;
		UCA0CTL1 |= UCSSEL_2;                     // SMCLK
		UCA0BR0 = 208;//130;                            // 16MHz 9600 PREESCALAR
		UCA0BR1 = 0;//6;                             //(UCAxBR0 + UCAxBR1 � 256)
		UCA0MCTL =0X00;//0x0c;//UCBRS0;                        // Modulation UCBRSx = 1
		UCA0CTL1 &= ~UCSWRST;
		IE2 |= UCA0RXIE;
	}

	void clk_init()
	{
		WDTCTL = WDTPW + WDTHOLD;                 // Stop WDT
		BCSCTL1 =CALBC1_16MHZ;
		BCSCTL2 =DIVS_3;
		DCOCTL = CALDCO_16MHZ;

	}


	void port1interrupt()
	{
		P2DIR&=~0x01;
		P2DIR|=0x04;

		P2SEL&=~0x09;
		P2SEL2&=~0x09;
		P2OUT=0X00;
		P2REN=0X00;
		P2IE=0X01; //Habilita la interrupcion asociada a P1IFG
		P2IFG=0X00; // set when a interrupt ocurrs
		P2IES=0X00; // INTERRUPT EDGE SELECT  , 0 MEANS low-to-high transition, 1 means a high-to-low transition
	}

	void port2interrupt()
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

	void eventosexternos()
	{

/*		P2OUT=0X00;
		P2DIR&=(~0X01);
		P2SEL|=0X01;
		P2SEL2&=(~0X01);
		P2REN=0X00;

		TA1CTL=ID_3|TASSEL_2|MC_2;
		TA1CCTL0=CAP|CM_3|CCIE|SCS;
*/
		P2OUT=0X00;
		P2DIR&=~(BIT2|BIT3|BIT4);
		P2SEL|=(BIT2);
		P2SEL2&=~(BIT2);
		P2REN=0X00;

        P2OUT=0X00;
        TA1CTL=TASSEL_2|MC_2|TAIE|ID_3;
        TA1CCTL1=CAP|CM_3|CCIE |SCS;//|CCIS_1

	}

	void ADC10f()
			{
				ADC10CTL1 	 = 		INCH_5|ADC10DIV_4|CONSEQ_2	;           // CHANEL INPUT AND MODE
				ADC10CTL0 	 = 		ADC10SHT_3|ADC10SR|REFBURST|MSC|REF2_5V|REFON | ADC10ON | ADC10IE;  // REFERENCE AND TIMING
				ADC10AE0 	|= 		BIT5;                        //ENABLE THE ANALOG CHANNEL ADC option�
			}

	void initADC10()
	{
		ADC10CTL0	|=		(ENC|ADC10SC ) ;
	}


	void inicio()
	{
		clk_init();
		uart_init();
		//eventosexternos();

		 port1interrupt();

		Enableinterrupts();

	}


	#endif /* FBF_H_ */
