#include <msp430.h> 

/*
 * main.c
 */
int main(void)

{
	WDTCTL =   WDTPW   +   WDTHOLD;    //  Stop    watchdog    timer
	P2DIR=BIT7;
		P2SEL  |=  (BIT6   |   BIT7);  //  Set P2.6    and P2.6    SEL for XIN,    XOUT
		P2SEL2 &=  ~(BIT6|BIT7);   //  Set P2.6    and P2.7    SEL2    for XIN,    XOUT
//	P2SEL  |=  (BIT6   |   BIT7);  //  Set P2.6    and P2.6    SEL for XIN,    XOUT
	//P2SEL2 &=  ~(BIT6|BIT7);   //  Set P2.6    and P2.7    SEL2    for XIN,    XOUT

	/* Select  32kHz   Crystal for ACLK    */
	BCSCTL1    &=  (~XTS); //  ACLK    =   LFXT1CLK
	BCSCTL3    &=  ~(BIT4|BIT5);   //  32768Hz crystal on  LFXT1



		P1SEL|= (BIT0|BIT4);
		P1SEL2 &=  ~(BIT0|BIT4);
		P1DIR  |=  (BIT0|BIT4);

while(1);

}
