#include <msp430.h> 
#include "CDC.h"
#include "FBF.h"
/*
 * RealTimceClock3285.c
 *
 * This file contains a basic application of the chip bq3285
 *
 *
 *
 *
 *
 * Pin Assignament
 *
 *
 *
 * Port 1 P1						Port 2 P2
 *
 * P1.0   AD7						P2.0	AD1
 * P1.1   RX                        P2.1	AD0
 * P1.2   TX                        P2.2    AS
 * P1.3   AD4                       P2.3	AD5
 * P1.4   AD3                       P2.4	AD6
 * P1.5   AD2                       P2.5
 * P1.6   R/~W                      P2.6
 * P1.7   DS                        P2.7
 *
 *
 *AS latch the adress int to the IC, with a falling edge;
 *DS latch write data to the chip
 *r/-w rising laches data in to device
 *
 */
#define secR   0x00
#define minR   0x02
#define hourR  0x04
#define dayR   0x06
#define monthR 0x08
#define yearR  0x09
#define regA   0x0A
#define regB   0X0B
#define regC   0X0C
#define regD   0X0D

#define	AD0_BIT BIT0  //P2
#define AD1_BIT BIT1  //P2
#define AD2_BIT BIT2  //P2
#define AD3_BIT BIT3  //P2
#define AD4_BIT BIT4  //P2
#define AD5_BIT	BIT5  //P2
#define AD6_BIT BIT6  //P2
#define AD7_BIT	BIT7  //P2

#define AS_BIT	 BIT3
#define DS_BIT	 BIT5
#define RW_BIT   BIT4

unsigned int year1,day1,hour1,min1,sec1;

char WR_RTC(char,char);
void read_t(char);
void Write_t(char,char);
void adress_data(char);
void write_reg(char);
int main(void)
		{
			inicio();



			while(1)
			{


			}




		}




		 void read_t(char adrrss)
		 {

			P1OUT|=DS_BIT;
			P1OUT|=RW_BIT;


			/*start Register Adress phase*/
				P2DIR=0XFF;
				P2OUT=adrrss;
				P1OUT&=~AS_BIT;
				P1OUT|=RW_BIT;
			/*end Register Adress phase*/

			P2DIR=0X00;


			P1OUT&=~DS_BIT;
			P1OUT|=RW_BIT;
			adrrss=P2IN;

			P1OUT|=DS_BIT;

		 }

		void write_t(char adress_d,char data_ss)
		{

			P1OUT|=DS_BIT;
			/*start Register Adress phase*/
				P2DIR=0XFF;
				P2OUT=adress_d;
				P1OUT|=AS_BIT;
				_delay_cycles(1000000);
				P1OUT&=~AS_BIT;
				P1OUT|=RW_BIT;
			/*end Register Adress phase*/

		_delay_cycles(1000000);

			/*start Register data phase*/
				P2OUT=data_ss;

				P1OUT|=AS_BIT;
				P1OUT|=RW_BIT;

			/*end Register data phase*/
				_delay_cycles(1000000);

		}


	#pragma vector=USCIAB0RX_VECTOR
	__interrupt void SerialReceiver_ISR(void )
	{
		IFG2&=~UCA0RXIFG;
		write_t(0x0A,0x07);
		line_jump();uart_send_string(" Done A ");

		write_t(0x0B,0x08);
		uart_send_string(" Done B");
	}
