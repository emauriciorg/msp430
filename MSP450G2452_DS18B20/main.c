#include <msp430g2452.h>
#include "ishan.h"
#include "ds18x20.h"

float temperature=0;
void main()

{
   
   	WDTCTL = WDTPW + WDTHOLD; // Stop watchdog timer
	
	//setup DCO to 1MHZ
	BCSCTL1 = CALBC1_16MHZ;
	DCOCTL = CALDCO_16MHZ;   
	
	//General GPIO Defines
	LED_DIR |= (LED_0 + LED_1); // Set P1.0 and P1.6 to output direction
	LED_OUT &= ~(LED_0 + LED_1); // Set the LEDs off
	
	InitDS18B20();
	
	for(;;)
	{	
		
		temperature=GetData();
		delay_ms(100);
		
	}
	
}
