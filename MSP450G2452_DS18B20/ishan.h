#ifndef ISHAN_H_
#define ISHAN_H_

#define LED_0 		BIT0 
#define LED_1 		BIT6
#define LED_OUT 	P1OUT
#define LED_DIR 	P1DIR
#define LED_SEL		P1SEL
#define HIGH	1
#define LOW		0
#define TRUE	1
#define FALSE	0
#define PULSE_LED0	P1OUT|=LED_0;delay_us(10);P1OUT&=~LED_0;
#define PULSE_LED1	P1OUT|=LED_1;delay_us(10);P1OUT&=~LED_1;
#define LED0_ON		P1OUT|=LED_0;
#define LED1_ON		P1OUT|=LED_1;
#define LED0_OFF	P1OUT&=~LED_0;
#define LED1_OFF	P1OUT&=~LED_1;
void delay_ms(int);
void delay_us(int);

#endif /*ISHAN_H_*/
