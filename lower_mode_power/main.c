#include <msp430.h> 
#include"FBF.h"
/*
 * main.c
 */
unsigned int countt=0,count_t=0,secc=0;
		int main(void)
		{
			inicio();

			  P1OUT=BIT3;
			  _BIS_SR(LPM0_bits+GIE);        // Enter LPM0

			  //_bis_SR_register(LPM3_bits + GIE);


		}
#pragma vector=PORT1_VECTOR
		__interrupt void puerto_1(void)
		{
			//TACTL&=~(BIT5|BIT4);


			//_bic_SR_register(LPM3_bits);

			P1IFG=0;
   			if(secc>2){	TACTL|=TACLR;count_t=0;secc=0;countt=0;}
			if((countt>1)&&(count_t>2)){
			TACTL|=TACLR;secc=0;count_t=0;countt=0;P1OUT^=BIT6; _BIS_SR(LPM0_bits+GIE);  }
			else{  _BIC_SR(LPM0_bits);        TACTL|=TASSEL_2|TAIE|MC_1;TA0CCR0|=31250;countt++;}
//			_bic_SR_register_on_exit(LPM3_bits);

		}
#pragma vector=TIMER0_A1_VECTOR
		__interrupt void timer_a1(void)
		{
			   TACTL&=~TAIFG;
			if(count_t==4){secc++;count_t=0;}else{count_t++;}
		if(secc>2){	TACTL|=TACLR;count_t=0;secc=0;countt=0;}

		}
