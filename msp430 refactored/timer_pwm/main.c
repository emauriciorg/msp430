/**
 * @file main.c
 * @author mauror , github:emauriciog
 * @brief 
 * @version 0.1
 * @date 2020-10-03
 * 
 * @copyright Copyright (c) 2020
 * 
 */

/*
	This programs can produce a soft PWM signal in the leds pins
	and a hardware PWM signal in the pint P2.0,P2.1 and P2.2
	
	The PWM period and duty cycle can be changed via uart 9600 8N1
	
	timer_tick_period  =source_clk / divider(1,2,4,8)
	
	pwm period = (timer_tick_period* CCR0)
	pwm_duty_cycle_off =(timer_tick_period*CCR1..2)   
	pwm_duty_cycle_ON =pwm period - (timer_tick_period*CCR1..2)   

*/

#include <msp430.h>
#include <stdbool.h>
#include <stdint.h>

#include"CDC.h"

#define TIMER_MODE_TOGGLE (BIT7) /*useful to create square waves*/
#define TIMER_MODE_RESET_SET (BIT7|BIT6|BIT5) /*useful to for HW PWM ccr0 and crrX*/
#define TIMER_MODE_SET_RESET (BIT6|BIT5) /*useful to for HW PWM ccr0 and crrX*/

#define TIMER1_INTERRUPT_VECTOR_ENABLED
#define TIMER_MODE_CONTINUOUS (BIT5)

struct soft_pwm_st{
	uint16_t period;
	uint16_t ticks;		
};


unsigned char rowcnt;               // row counter
unsigned char colcnt;               // column counter
unsigned char g_matrix[8];            // content for LED matrix
unsigned char r_matrix[8];          // content for red LED matrix
unsigned char g_row;                // current row of the green LED matrix
unsigned char r_row;                // current row of the red LED matrix
unsigned char col_done=0;

volatile struct soft_pwm_st soft_pwm;


void enable_interrupts(void);
void clk_init(void);
void timer_init(char trigger_timer);
void leds_init(void);
void uart_init(void);



int main(void)
{
	clk_init();
	uart_init();
	leds_init();
	timer_init(true);
	enable_interrupts();

	while(1){	
		uart_send_string("T1 ");
		print_uint( soft_pwm.period/*TACCR0*/);
		line_jump();
		/*might need a flag or delay here to avoid blowing up the serial*/
	}

}



void uart_init(void)
{
	/*Choose alternative io function , in this case UART pins*/
	P1SEL    |= ( BIT1|BIT2);
	P1SEL2   |= ( BIT1|	BIT2);

	/*Puts the module under reset*/
	UCA0CTL1  = UCSWRST;
	UCA0CTL1 |= 0x80;                     // SMCLK
	
	/*baud rate setup: (UCAxBR0 + UCAxBR1 / 256, @ 16MHz 9600 PREESCALAR) */
	UCA0BR0 = 130;
	UCA0BR1 = 6;
	
	UCA0MCTL =0x0c;//UCBRS0, Modulation UCBRSx = 1
	UCA0CTL1 &= ~UCSWRST;

	/*Enable RX isr*/
	IE2 = UCA0RXIE;
}


void timer_init(char trigger_timer)
{

	if(trigger_timer)
	{
		/*TAIE general timer counter interrupt is disabled*/
		TA1CTL   = ID_1|TASSEL_2| TIMER_MODE_CONTINUOUS; /*controls timer A1*/
	
		TA1CCTL0 = TIMER_MODE_SET_RESET ; /*controls timer A1 output0*/
		TA1CCTL1 = TIMER_MODE_SET_RESET ; /*controls timer A1 output0*/
		TA1CCTL2 = TIMER_MODE_SET_RESET ; /*controls timer A1 output0*/
		
		/*Just random values to test square wave(use formula otherwise)*/
		TA1CCR0 = 16000;//32767;
		TA1CCR1 = 4000;//2047;
		TA1CCR2 = 32767;
		

		/*Choose alternative io function , in this case timerA_out0-1*/
		P2SEL2 &=~ (BIT0|BIT1|BIT2|BIT6|BIT5);
		P2SEL  |=  (BIT0|BIT1|BIT2|BIT6|BIT5);
		P2DIR  |=  (BIT0|BIT1|BIT2|BIT6|BIT6);
		P2OUT  &=~ (BIT0|BIT1|BIT2|BIT6|BIT6);
		
		TA1CCTL0|=CCIE;
//		TA1CCTL1|=CCIE;
//		TA1CCTL2|=CCIE;

	}else
	{
		/*Clear timers*/
		TA1CTL = 0;

		TA1CCR0  = 0;
		TA1CCR1  = 0;

		TA1CCTL0 = 0;
		TA1CCTL1 = 0;
	}
}


void enable_interrupts(void)
{
	_BIS_SR(GIE);
	__enable_interrupt();
	__bis_SR_register(GIE);
}


void clk_init(void)
{
	WDTCTL  = WDTPW | WDTHOLD;// Stop WDT
	BCSCTL1 = CALBC1_16MHZ;
	BCSCTL2 = 0x00;
	DCOCTL  = CALDCO_16MHZ;
}

void leds_init(void){
	P1SEL&=~(BIT0|BIT6);
	P1SEL2&=~(BIT0|BIT6);	
	P1DIR|=(BIT0|BIT6);
	P1OUT&=~(BIT0|BIT6);
	P1OUT |=(BIT6|BIT0);
}


/*---------------------------------ISR SECTION--------------------------------*/


#pragma vector=USCIAB0RX_VECTOR
__interrupt void rx_serial_isr(void)
{
	volatile char rx_byte;

	IFG2 &= ~UCA0RXIFG;

	rx_byte = UCA0RXBUF;
	
	switch(rx_byte){

	/*soft pwm*/
	case 'q': soft_pwm.period += 1; break;
	case 'a': soft_pwm.period -= 1; break;
	case 'z': soft_pwm.period  = 000; break;
	
	/*hard pwm duty*/
	case 'w':  TACCR1+= 100; break;
	case 's':  TACCR1-= 100; break;
	case 'x':  TACCR1 = 6000; break;
	case 'f':  TACCR1 = 000;  break;

	/*hard pwm period*/
	case 'W': TACCR0+= 100; break;
	case 'S': TACCR0-= 100; break;
	case 'X': TACCR0 = 6000; break;
	case 'F': TACCR0 = 000;  break;


	case '1':{ timer_init(true);}break;
	case '2':{ timer_init(false);}break;
	default : break;	
	}
}


#ifdef TIMER1_INTERRUPT_VECTOR_ENABLED
#pragma vector=TIMER1_A1_VECTOR
__interrupt void TIMER_A1_isr(void)
{
	if(TA1CCTL1 & CCIE){
	    TA1CCTL1 &= ~CCIFG;
	//      TA1CCR1 +=2048;
	}
	if(TA1CCTL2 & CCIE){
	    TA1CCTL2 &= ~CCIFG;
	  //    TA1CCR2 +=10000;

	  	P1OUT^=BIT6; /*blinks green led*/
	}
	if(TA1CTL & TAIFG){
	    TA1CTL    &= ~TAIFG;
	}

	//P1OUT^=BIT0; /*blinks red led*/
}

//i am getting the output in p2.2 
#pragma vector=TIMER1_A0_VECTOR
__interrupt void TIMER_A10_isr(void)
{
	if(TA1CCTL0 & CCIE){
	    TA1CCTL0 &= ~CCIFG;
		//column update(g_matrix[rowcnt]);
	
		if(col_done){
			P1OUT&=~BIT0;
			col_done =0;
		}		
	
		if (rowcnt==7){
			rowcnt=0;
		}else{
			rowcnt++;
		}
		

		if(colcnt == 7)                 // When on last column of matrix
		{
			col_done =1;
			P1OUT|=BIT0; /*blinks red led*/
			//TB0CCR3 = TB0CCR0;
			rowcnt=0;
			colcnt=0;
	
		} else { 
			colcnt++;
		}
	}

}
	



#pragma vector=COMPARATORA_VECTOR
__interrupt void comparator_vector(void)
{
	if(TA1CCTL0 & CCIE){
	    TA1CCTL0 &= ~CCIFG;}
	if(TA1CCTL1 & CCIE){
	    TA1CCTL1 &= ~CCIFG;}
	if(TA1CCTL2 & CCIE){
	    TA1CCTL2 &= ~CCIFG;
	//	P1OUT^=BIT6; /*blinks green led*/
	}
	if(TA1CTL & TAIFG){
	    TA1CTL    &= ~TAIFG;
	}

//	P1OUT^=BIT0; /*blinks red led*/
}

#endif


#if 1
///def TIMER0_INTERRUPT_VECTOR_ENABLED
#pragma vector=TIMER0_A0_VECTOR
__interrupt void TIMER_A0_isr(void)
{

	if(TA0CCTL0 & CCIE)TA0CCTL0 &= ~CCIFG;
	if(TA0CTL & TAIFG)TA0CTL    &= ~TAIFG;

	if(soft_pwm.ticks < soft_pwm.period){
		soft_pwm.ticks++;
	}else{
		soft_pwm.ticks=0;
	}
	//P1OUT^=BIT6; /*blinks green led*/
}
#endif

