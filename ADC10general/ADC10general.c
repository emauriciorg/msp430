#include <msp430.h> 
#include "FBF.h"
#include "CDC.h"

volatile unsigned int nADC;
/*
 *
 *
 *
 * ADC10general.c
 */

    void  main(void)
	{
    	inicio();
    			ADC10CTL1 	 = 		INCH_7|ADC10DIV_4;//|CONSEQ_2	;           // CHANEL INPUT AND MODE
    			ADC10CTL0 	 = 		ADC10SHT_3|ADC10SR|REFBURST|MSC|REF2_5V|REFON | ADC10ON ;  // REFERENCE AND TIMING
    			ADC10AE0 	|= 		BIT7;                        //ENABLE THE ANALOG CHANNEL ADC optionç



    		/*	ADC10CTL0	|=		(ENC|ADC10SC ) ;
    					while((ADC10CTL0&ADC10IFG) !=ADC10IFG);
    					ADC10CTL0&=~ADC10IFG;
    					nADC=ADC10MEM;
	*/
    			nADC=10;
    			enin();
    			while(1)
		{

    				   ec("Numero adc es ");  printuint(nADC);   borrar();
			ADC10CTL0	|=		(ENC|ADC10SC ) ;
			while((ADC10CTL0&ADC10IFG) !=ADC10IFG);
			nADC=ADC10MEM;
			ADC10CTL0&=~ADC10IFG;



		}

	}


	#pragma vector=ADC10_VECTOR
    __interrupt void adc10_ISR(void)
    {

    	ADC10CTL0 &=~ ADC10IFG;

    	nADC=ADC10MEM;

    }
