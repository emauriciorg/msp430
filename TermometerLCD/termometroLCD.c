/*
 * egg2.c
 *
 *  Created on: 28/06/2016
 *      Author: Mauricio
 */



		#include <msp430.h>
		#include"FBF.h"
		#include"CDC.h"
	


	unsigned int    FanCount=0,nAdc=BIT0;
	unsigned int	TempVolt[8]={0};
	unsigned int 	TempC[7]={0};
	unsigned int 	TempCA[5]={0};

	unsigned int 	upp=0;


	void controlTemp(unsigned int);






		void controlTemp(unsigned TempC)
		{
			if((TempC<370)&&(upp==0))
			{
				P1OUT&=~BIT3;
				if(TempC==390){upp=1;}

			}else
			{

				if(TempC>370){upp=0;P1OUT|=BIT3;}

			}





		}



void TempSample(){

	    TempVolt[4]=TempVolt[3];
	    TempVolt[3]=TempVolt[2];
	    TempVolt[2]=TempVolt[1];
		TempVolt[1]=TempVolt[0];
		TempVolt[5]=(TempVolt[1]+TempVolt[2]+TempVolt[3]+TempVolt[4])/4;
			//function to shown temperature;
				TempC[5]=TempC[4];
				TempC[4]=TempC[3];
				TempC[3]=TempC[2];
				TempC[2]=TempC[1];
			    TempC[1]=TempC[0];
		        _delay_cycles(100);
				TempC[0]=(((TempVolt[5]*5.1)-662));
				TempC[6]=(TempC[1]+TempC[2]+TempC[3]+TempC[4]+TempC[5]+TempC[6])/6;

				TempCA[0]=TempC[6]/10;

				TempCA[1]=TempCA[0]*10;

				TempCA[2]=TempC[6]-TempCA[1];

				 if(TempCA[2]>6){TempCA[3]=TempCA[1]+10;}else{ TempCA[3]=TempCA[1];}



}


void main(void)


{
	inicio();

	ADC10CTL1 	 = 		INCH_5|ADC10DIV_7|CONSEQ_2	;           // CHANEL INPUT AND MODE
			ADC10CTL0 	 = 		ADC10SHT_3|MSC| ADC10ON | ADC10IE;  // REFERENCE AND TIMING
			ADC10AE0 	|= 		BIT5;                        //ENABLE THE ANALOG CHANNEL ADC optionç
	enin();
	inicioADC();


		P2SEL2=0X00;
		P2SEL=0X00;
		P2DIR=0XFF;
		P2OUT=0;






 	 while(1)
 	{


TempSample();

 				//controlTemp(TempC[2]);
 				ec("temp ");printuint(TempC[6]);espacio();printuint(TempCA[3]); borrar();

 				_delay_cycles(10000);


 		 // controlTemp(TempC[2]);

 	}
 }


#pragma vector=ADC10_VECTOR
__interrupt void adc10_isr(void)
{
		TempVolt[0]=ADC10MEM;




	ADC10CTL0&=~ADC10IFG;
}
/*
int adc[10] = {0}; //Sets up an array of 10 integers and zero's the values
int avg_adc[8] = 0;

// Function prototypes
void adc_Setup();
void adc_Sam10();

void main()
{

		inicio();
	  adc_Setup();						// Fucntion call for adc_setup

	  while(1)
	  {
		  adc_Sam10();		// Function call for adc_samp

		  // Add all the sampled data and divide by 10 to find average
		  avg_adc[5]=avg_adc[4];
		  avg_adc[4]=avg_adc[3];
		  avg_adc[3]=avg_adc[2];
		  avg_adc[2]=avg_adc[1];
		  avg_adc[1]=avg_adc[0];
		  avg_adc[0] = (((adc[0]+adc[1]+adc[2]+adc[3]+adc[4]+adc[5]+adc[6]+adc[7]+adc[8]+adc[9]) / 10)*5.1)-662;
		  avg_adc[6]=(avg_adc[5]+avg_adc[1]+avg_adc[2]+avg_adc[3]+  avg_adc[4])/5;


			ec("temp ");printuint(avg_adc[6]); borrar();
	  }
}
*/
/*
// ADC10 interrupt service routine
#pragma vector=ADC10_VECTOR
__interrupt void ADC10_ISR(void)
{
  __bic_SR_register_on_exit(CPUOFF);        // Clear CPUOFF bit from 0(SR)
}

// ADC set-up function
void adc_Setup()
{
	ADC10CTL1 = CONSEQ_2 + INCH_7;						// Repeat single channel, A0
	ADC10CTL0 = ADC10SHT_2 + MSC + ADC10ON + ADC10IE;	// Sample & Hold Time + ADC10 ON + Interrupt Enable
	ADC10DTC1 = 0x0A;									// 10 conversions
	ADC10AE0 |= BIT7;									// P1.0 ADC option select
}

// ADC sample conversion function
void adc_Sam10()
{
    ADC10CTL0 &= ~ENC;				// Disable Conversion
    while (ADC10CTL1 & BUSY);		// Wait if ADC10 busy
    ADC10SA = (int)adc;				// Transfers data to next array (DTC auto increments address)
    ADC10CTL0 |= ENC + ADC10SC;		// Enable Conversion and conversion start
    __bis_SR_register(CPUOFF + GIE);// Low Power Mode 0, ADC10_ISR
}
*/
