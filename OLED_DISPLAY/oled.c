#include <msp430g2553.h>
#include"CDC.h"
#include"FBF.h"
#include"ssd1306.h"
/************************************VARIABBLE AND MACROS******************************************************/
volatile char DES=0,flag11;
volatile char sec_t=0,min_t=0,hour_t=0,day_t=0,I_I=0,SerOK=0,side_t='0',G_IRA='0';
volatile unsigned char COUNTT=75,countt=0,count_t=0;
volatile unsigned char TCOUNTT=100,Tcountt=0,Tcount_t=0;


unsigned int T1,T2,T3;
		char signo='p';
		unsigned char ifgt,count=0;
		unsigned int registro1;

		unsigned int GZH,GZL,GAL,GAH;

		int DCOS;
		unsigned int nT=0;
		int GZ1,GZ2,GZ,anguloAproxX,anguloAproxY,anguloAproxZ,GX1,GX2,GY1,GY2;

/*************************************FUNCTION DECLARATION******************************************************/

		void setHour()
		{
			gw(secc,0);
			gw(minn,8);
			gw(horr,5);

		}
  char BCDtoChar(unsigned char imbcd)
  {

	  return imbcd=imbcd+48;


  }

		void i2cmaster()
			{

				  P1OUT &= ~BIT0;                           // P1.0 = 0
				  P1DIR |= BIT0;                            // P1.0 output
				  P1SEL |= BIT6 + BIT7;                     // Assign I2C pins to USCI_B0
				  P1SEL2|= BIT6 + BIT7;                     // Assign I2C pins to USCI_B0
				  UCB0CTL1 |= UCSWRST;                      // Enable SW reset
				  UCB0CTL0 = UCMST + UCMODE_3 + UCSYNC;     // I2C Master, synchronous mode
				  UCB0CTL1 = UCSSEL_2 + UCSWRST;            // Use SMCLK, keep SW reset
				  UCB0BR0 = 12;                             // fSCL = SMCLK/12 = ~100kHz
				  UCB0BR1 = 0;
				  UCB0I2COA = 0;                         // Own Address is 048h
				  UCB0I2CSA =0x3C;//0XD7>>1;// SADHR>>1; SLAVE DIRECTION
				  UCB0CTL1 &= ~UCSWRST;                     // Clear SW reset, resume operation
				 IE2=0;
			}

    void enable_interrupts();

/*
	void setGyro();
	int DCoffset();
	int angle(int);
*/
	int twoc2dec(unsigned int );

	void timer0()
	{
		TA0CCR0=8000;
		TACCTL0=CCIE; //no capture mode+CCIA+Asynchronous en capture mode+modo comparacion+
		TACTL=TASSEL_2|MC_1|TAIE;//ID_3|
	}

	/****************************************MAIN CODE**************************************************************/


	int main(void)
	{

		inicio();
//		timer0();
		i2cmaster();

	 	enable_interrupts();

	 	setHour();
		while(1)
		{
/*
   			SetCursorPosition(0, 0);
   			PrintStr("x:");Lp_ui(twoc2dec(anguloAproxX));
   			SetCursorPosition(2, 0);
   			Lp_ui(twoc2dec(GX1));putme(' ');putme(signo);
*/
   			uart_send_string(" hora ");/*p_ui(hour_t);*/
   			putmes(BCDtoChar((hour_t&0xf0)>>4));putmes(BCDtoChar(hour_t&0x0f));putmes(':');
   			putmes(BCDtoChar((min_t&0xf0)>>4));putmes(BCDtoChar(min_t&0x0f));putmes(':');
   			putmes(BCDtoChar((sec_t&0xf0)>>4));putmes(BCDtoChar(sec_t&0x0f));c_lc();
			//uart_send_string(" Y: ");print_uint(twoc2dec(GY1));espacio();print_uint(twoc2dec(anguloAproxY));espacio();uart_write_byte(signo);
			//uart_send_string(" Z: ");print_uint(twoc2dec(GZ1));espacio();print_uint(twoc2dec(anguloAproxZ));espacio();uart_write_byte(signo);line_jump();
			sec_t=gr(secc);
			min_t=gr(minn);
			hour_t=gr(horr);

	    //showLCD();




		}
	}

	int twoc2dec(unsigned int twoc)
			{
				signo='+';
				if((twoc&0x8000)==0x8000)
				{
				twoc=(~twoc)+1;
				signo='-';
				}
				return twoc;
			}



	/*int angle(int angle) Funcion angle return the actual angle and corrects the data
	{
		if(angle<360)
		{
			angle-=360;
		}else if(angle>360)
		{
		 angle+=360;

		}
		return angle;
	}


	int DCoffset(){//This function determines how much noise is on the gyro,set once at start

		int DCe,eer=0;
		for(DCe=0;DCe<=100;DCe++)
		{

			GZL=gr(OUT_Z_L );
			GZH=gr(OUT_Z_H );
			GZ=(GZH<<8)|GZL;
			eer=eer+GZ;
		}
		eer=eer/100;
		return eer;
	}



*/
	 void timer0_en()
	      {

	 	   TACTL	 = ID_3|TASSEL_2|MC_1; //UP mode
		   TACCR0	 = 40;
		   TACCTL0 =OUTMOD_7;
		   TACCR1=0;

	      }


	void enable_timer()
			{
			TA1CTL	 = ID_3|TASSEL_2|MC_1; //UP mode
			TA1CCR0	 = 2000;
			TA1CCTL1 =OUTMOD_7| CCIE;
			TA1CCR1=000;
			}

	   void enable_interrupts()
	 		{
	 			_BIS_SR(GIE);
	 			__enable_interrupt();
	 			__bis_SR_register(GIE);
	 		}

/*************************************INTERRUPT*******************************************/
/*
	#pragma vector=USCIAB0RX_VECTOR
	__interrupt void RXserial_isr(void)
	{
		IFG2&=~UCA0RXIFG;
		DES=UCA0RXBUF;
		switch(DES)
		{
			case 'q':{	if(COUNTT<999){COUNTT+=1;}	}break;
			case 'a':{	if(COUNTT>1){COUNTT-=1;}	}break;
			default: COUNTT=COUNTT;
		}
	}
*/
/*
#pragma vector=TIMER0_A0_VECTOR
__interrupt void TIMER_A0_VECTOR(void)
{
	TA0CCTL0&=~CCIFG;
	TA0CTL&=~TAIFG;

	if(nT==2)
	{	nT=0;
		anguloAproxZ+=(GZ1+GZ2)*0.01;
		anguloAproxX+=(GX1+GX2)*0.01;
		anguloAproxY+=(GY1+GY2)*0.01;

		//integro

	}else
	{

		GX2=GX1;
		GAL=gr(OUT_X_L );
		GAH=gr(OUT_X_H );
		GX1=((GAH<<8)|GAL);//-10;

		GZ2=GZ1;
		GAL=gr(OUT_Z_L );
		GAH=gr(OUT_Z_H );
		GZ1=((GAH<<8)|GAL);//-10;

		GY2=GY1;
		GAL=gr(OUT_Y_L );
		GAH=gr(OUT_Y_H );
		GY1=((GAH<<8)|GAL);//-10;


		nT++;
	}

}
*/
