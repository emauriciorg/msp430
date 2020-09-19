#include <msp430.h> 
#include <stdint.h>

/**
 * @brief 
 * 
 30 minutes
 */

/*----------------------macros-----------------------------------------------*/

#define LED_RED_IN    P1IN
#define LED_RED_OUT   P1OUT
#define LED_RED_DIR    P1DIR
#define LED_RED_PIN    BIT0


#define LED_GREEN_IN   P9IN
#define LED_GREEN_OUT  P9OUT
#define LED_GREEN_DIR  P9DIR
#define LED_GREEN_PIN  BIT7

#define BUTTON_1_IN   P1IN
#define BUTTON_1_OUT  P1OUT
#define BUTTON_1_DIR  P1DIR
#define BUTTON_1_PIN  BIT1

#define BUTTON_2_IN   P1IN
#define BUTTON_2_OUT  P1OUT
#define BUTTON_2_DIR  P1DIR
#define BUTTON_2_PIN  BIT2


/*
	TODO:Check PxSEL0
*/

/*----------------------private functions--------------------------------------*/
void init_leds(void);
void init_buttons(void);

void init_wdt(void);
void init_power_managment(void);


int main(void)
{
	init_wdt();
	init_power_managment();
	init_leds();
	init_buttons();
	
	while(1){
		if (BUTTON_1_IN&BUTTON_1_PIN) {
			LED_GREEN_OUT |= LED_GREEN_PIN;
		}else{
			LED_GREEN_OUT &= ~LED_GREEN_PIN;
		}

		if (BUTTON_2_IN&BUTTON_2_PIN) {
			LED_RED_OUT |= LED_RED_PIN;
		}else{
			LED_RED_OUT &= ~LED_RED_PIN;
		}
	}
	return 0;
}


void init_wdt(void)
{
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer
}

void init_power_managment(void)
{
	PM5CTL0 &= ~LOCKLPM5;
}

void init_buttons(void)
{
	BUTTON_1_DIR &= ~BUTTON_1_PIN;
	BUTTON_2_DIR &= ~BUTTON_2_PIN;
}

void init_leds(void)
{
	LED_GREEN_DIR |= LED_GREEN_PIN;
	LED_RED_DIR   |= LED_RED_PIN;
}

