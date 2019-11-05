#include "msp430G2553.h"


void main(void)
{
 WDTCTL = WDTPW + WDTHOLD;  // Stop WDT


 P1DIR |= BIT2|BIT5|BIT6;             // P1.2 to output
 P1SEL |= BIT2|BIT5|BIT6;             // P1.2 to TA0.1


 CCR0 = 1000-1;             // PWM Period
 CCTL1 = OUTMOD_7;          // CCR1 reset/set
 CCR1 = 250;                // CCR1 PWM duty cycle
 TACTL = TASSEL_2 + MC_1;   // SMCLK, up mode


 _BIS_SR(LPM0_bits);        // Enter LPM0
}
