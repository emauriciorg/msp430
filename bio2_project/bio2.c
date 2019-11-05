#include <msp430g2553.h>
#include"CDC.h"

volatile char voice,voice1,voice3,voice4,voice2,voice5,voice6,voice7,voice8,voice9,temp2;


	void uart()
		{
					P1SEL |= ( BIT1|BIT2);
			P1SEL2 |= ( BIT1|	BIT2);
			UCA0CTL1 = UCSWRST;
			UCA0CTL1 |= 0x80;                     // SMCLK
			/*UCA0BR0 = 130;                            // 16MHz 9600 PREESCALAR
			UCA0BR1 = 6;                             //(UCAxBR0 + UCAxBR1 × 256)
			*/
/*			UCA0BR0 = 138;                            // 16MHz 9600 PREESCALAR
			UCA0BR1 = 0;                             //(UCAxBR0 + UCAxBR1 × 256)

			UCA0MCTL =0x0E;//UCBRS0;                        // Modulation UCBRSx = 1
	*/
			UCA0BR0 = 130;                            // 16MHz 9600 PREESCALAR
					                             //(UCAxBR0 + UCAxBR1 × 256)

					UCA0MCTL =0x0C;//UCBRS0;                        // Modulation UCBRSx = 1

			UCA0CTL1 &= ~UCSWRST;
			IE2 &=~ UCA0RXIE| UCA0TXIE;
		}


 void Timer_block()

{


		   TA1CTL	 = ID_1|TASSEL_2|MC_1; //UP mode
		   TA1CCR0	 = 500;
		   TA1CCTL1 =OUTMOD_7| CCIE;
		   TA1CCR1=100;


		   P2SEL&=~(BIT0|BIT1);
		   P2SEL|=(BIT2|BIT1);

		   P2SEL2&=~(BIT0 |BIT1);
		   P2DIR|=BIT0|BIT1;

	   }

 void ADC10f()
 		{
 			ADC10CTL1 	 = 		INCH_5|ADC10DIV_7|CONSEQ_2	;           // CHANEL INPUT AND MODE
 			ADC10CTL0 	 = 		ADC10SHT_3|ADC10SR|REFBURST|MSC|REF2_5V|REFON | ADC10ON | ADC10IE;  // REFERENCE AND TIMING
 			ADC10AE0 	|= 		BIT5;                        //ENABLE THE ANALOG CHANNEL ADC optionç
 		}




 void Enin()
 		{
 			_BIS_SR(GIE);
 			__enable_interrupt();
 			__bis_SR_register(GIE);
 		}
	void clk()
		{
			WDTCTL = WDTPW | WDTHOLD;                 // Stop WDT
			BCSCTL1 =CALBC1_16MHZ;
			BCSCTL2 =0x00;
			DCOCTL = CALDCO_16MHZ;
		}


 void initADC10()
 {
 	ADC10CTL0	|=		(ENC|ADC10SC ) ;
 }
	int main(void)
	{
		clk();
		ADC10f();
		uart();

		Enin();
		initADC10();



		while(1){
        // ec("el dato es");borrar();
	        voice6=voice5/4;
			sd_(voice6);
			if(temp2>=127){temp2=0;	_delay_cycles(500000);}else{temp2++;}
            _delay_cycles(32000);

		};

	}


#pragma vector=ADC10_VECTOR
__interrupt void ADC10_in()
{
 	ADC10CTL0 &=~ ADC10IFG;

 	voice4=voice3;
    voice3=voice2;
 	voice2=voice1;
    voice1=voice;
    voice=ADC10MEM;

      //voice4=(voice+voice1+voice2+voice3)/4;
    voice5=(voice+voice1+voice2+voice3+voice4)/5;


}





#pragma vector=TIMER1_A1_VECTOR
	__interrupt void Timer1a1_isr(void)
	{

		TA1CCR1=voice;
		TA1CCTL1&=~CCIFG;

//		 if(i_n<19){i_n++;}else{i_n=0;}
	//	 TA1CCR1=Tono[i_n]+25;

	}
