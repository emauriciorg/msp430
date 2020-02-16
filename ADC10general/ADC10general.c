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
uint16 ADC10_sample(void)
{
	ADC10CTL0  |= (ENC|ADC10SC ) ;
	while((ADC10CTL0&ADC10IFG) !=ADC10IFG);
	ADC10CTL0&=~ADC10IFG;
	return ADC10MEM;
}

void ADC10_init(void)
{
	ADC10CTL1  = INCH_7|ADC10DIV_4;//|CONSEQ_2   // CHANEL INPUT AND MODE
	ADC10CTL0  = ADC10SHT_3|ADC10SR|REFBURST|MSC|REF2_5V|REFON | ADC10ON ;  // REFERENCE AND TIMING
	ADC10AE0  |= BIT7;                        //ENABLE THE ANALOG CHANNEL ADC option�
}
void  main(void)
{
	clk_init();
//	ADC10f();
	uart_init();
	ADC10_init();
	enable_interrupts();

	nADC = ADC10_sample();
while(1)
{

uart_send_string("Numero adc es ");  print_uint(nADC);   line_jump();
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
