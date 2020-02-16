#include <msp430.h> 
#include "STDBOOL.h"
#include "FBF.h"
#include "CDC.h"
//////////////////////////DHT11 handler/////////////////////////////////////////

#define DHT11 BIT4

unsigned char hum_int,hum_decimals,tmp_int,tmp_decimals,parity,parity_calc;

	bool dht11(void)
{
	volatile int elapsed_time=0,bit_cnt;
	volatile unsigned char temp;

	bool data_validity = false;
	P1DIR |= DHT11; // Makes the pin OUTput
	P1OUT &= ~DHT11;// Start condition generation for DHT11
	_delay_cycles(2000); // delays 1 milisecond for each scan

	P1OUT |= DHT11;// Start condition generation for DHT11

	P1DIR &= ~DHT11; // Makes the pin input

	P1IFG &= ~DHT11; // Clears pin flag, if high

	while((P1IN&DHT11)==DHT11); // wait till the slave puls the pin low
	///////////////// DHT11 has responded /////////////////////////////
	do {
	elapsed_time++; // check if the elapsed time = 80 uS
	} while ((P1IN&DHT11)==0);
	if(elapsed_time <=10)
	{
	elapsed_time = 0;
	do {
	elapsed_time++; // check if the elapsed time = 80 uS
	} while ((P1IN&DHT11)==DHT11);
	if(elapsed_time <=10)// check if the elapsed time = 80 uS
	{
	///////// humidity integer/////////////
	for(bit_cnt=0;bit_cnt <8;bit_cnt++) // for humidity first byte
	{
	while ((P1IN&DHT11)==0); // skip the lower 50 uS part
	elapsed_time = 0;
	do {
	elapsed_time++; // check if the elapsed time = 80 uS
	} while ((P1IN&DHT11)==DHT11);
	if(elapsed_time >5)
	{
	hum_int |= 0x01;
	hum_int <<= 1;
	}
	else
	{
	hum_int &= ~0x01;
	hum_int <<= 1;
	}
	}

	///////// humidity decimal/////////////
	for(bit_cnt=0;bit_cnt <8;bit_cnt++) // for humidity first byte
	{
	while ((P1IN&DHT11)==0); // skip the lower 50 uS part
	elapsed_time = 0;
	do {
	elapsed_time++; // check if the elapsed time = 80 uS
	} while ((P1IN&DHT11)==DHT11);
	if(elapsed_time >5)
	{
	hum_decimals |= 0x01;
	hum_decimals <<= 1;
	}
	else
	{
	hum_decimals &= ~0x01;
	hum_decimals <<= 1;
	}
	}
	///////// temperature integer/////////////
	for(bit_cnt=0;bit_cnt <8;bit_cnt++) // for humidity first byte
	{
	while ((P1IN&DHT11)==0); // skip the lower 50 uS part
	elapsed_time = 0;
	do {
	elapsed_time++; // check if the elapsed time = 80 uS
	} while ((P1IN&DHT11)==DHT11);
	if(elapsed_time >5)
	{
	tmp_int |= 0x01;
	tmp_int <<= 1;
	}
	else
	{
	tmp_int &= ~0x01;
	tmp_int <<= 1;
	}
	}
	///////// temperature decimal/////////////
	for(bit_cnt=0;bit_cnt <8;bit_cnt++) // for humidity first byte
	{
	while ((P1IN&DHT11)==0); // skip the lower 50 uS part
	elapsed_time = 0;
	do {
	elapsed_time++; // check if the elapsed time = 80 uS
	} while ((P1IN&DHT11)==DHT11);
	if(elapsed_time >5)
	{
	tmp_decimals |= 0x01;
	tmp_decimals <<= 1;
	}
	else
	{
	tmp_decimals &= ~0x01;
	tmp_decimals <<= 1;
	}
	}
	/////////Parity/////////////
	for(bit_cnt=0;bit_cnt <8;bit_cnt++) // for humidity first byte
	{
	while ((P1IN&DHT11)==0); // skip the lower 50 uS part
	elapsed_time = 0;
	do {
	elapsed_time++; // check if the elapsed time = 80 uS
	} while ((P1IN&DHT11)==DHT11);
	if(elapsed_time >5)
	{
	parity |= 0x01;
	parity <<= 1;
	}
	else
	{
	parity &= ~0x01;
	parity <<= 1;
	}
	}
}

}
parity_calc = hum_int+hum_decimals+tmp_int+tmp_decimals;
// if(hum_int<=0x4C)
// {
// humidity_low= true;
// }
// else
// {
// humidity_high= true;
// }
if(parity_calc == parity)
{
data_validity = true;

}
return data_validity;

}


void main(){
inicio();
//8Mhz clk_init frequency
	while(1)
	{
	/*	P1OUT|=DHT11;
		P1DIR|=DHT11;
		P1SEL&=~DHT11;
		P1SEL2&=~DHT11;
		P1OUT|=DHT11;
		P1OUT&=~P1OUT|=DHT11;;
		_delay_cycles(160000);//WAIT FOR ~18mS
		P1OUT|=DHT11;
		_delay_cycles(240);//WAIT FOR ~35uS
		P1DIR&=~DHT11;
		while(P1IN&DHT11==DHT11);

		while(P1IN&DHT11==DHT11);

		_delay_cycles(630);//WAIT FOR ~35uS
		do{
			_delay_cycles(400);
			data1|=(P1IN<<i);

		}while();
*/

	    uart_send_string("waiting");line_jump();
	}

}
