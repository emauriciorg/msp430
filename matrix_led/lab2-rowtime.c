/*--------------------------------------------------------
GEORGE MASON UNIVERSITY
ECE 447 - Lab2 Row Timing 
  P2.6 Row Clock
  P2.7 Row Initialization

Date:   Fall 2020
Author: Jens-Peter Kaps

Change Log:
20200912 Initial Version, Jens-Peter Kaps
--------------------------------------------------------*/

#include <msp430.h> 

void delay(void) {
    volatile unsigned loops = 25000; // Start the delay counter at 25,000
    while (--loops > 0);             // Count down until the delay counter reaches 0
}


int main3(void)
{
    unsigned char rowcnt;     // row counter

    WDTCTL = WDTPW | WDTHOLD; // stop watchdog timer

    P2DIR |= (BIT6 | BIT7);   // Make Port 2.6 and 2.7 outputs
    P2OUT &= ~(BIT6 | BIT7);  // Set ports to 0
    PM5CTL0 &= ~LOCKLPM5;     // Unlock ports from power manager

    rowcnt = 0;

    while(1)                    // continuous loop
    {
        delay();
        if(P2OUT & BIT6)                 // If row clock 1 -> place breakpoint here
            P2OUT &= ~BIT6;              //   Set row clock 0
        else {
            if(rowcnt == 7) {            // if on row 7
                P2OUT |= (BIT6 | BIT7);  //   Set row clock and row init 1
                rowcnt = 0;              //   set row counter back to 0
            } else {                     // for all other rows
                P2OUT |= BIT6;           //   only set row clock 1
                P2OUT &= ~BIT7;          //   set row init to 0
                rowcnt++;                //   increment row counter
            }
        }

    }
	
	return 0;
}
