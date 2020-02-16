		#include <msp430.h>
		#include"CDC.h"
		#include"FBF.h"
		#include<math.h>

		unsigned int Ncp=60000;
		unsigned char P2OUTaux,N1;
		float freqq;
unsigned char senuu[32]={
		 127  //0
		,133  //1
		,140  //2
		,146  //3
		,152  //4
		,158  //5
		,164  //6
		,170  //7
		,176  //8
		,182  //9
		,187  //10
		,193  //11
		,198  //12
		,203  //13
		,208  //14
		,213  //15
		,218  //16
		,222  //17
		,226  //18
		,230  //19
		,233  //20
		,237  //21
		,240  //22
		,243  //23
		,245  //24
		,248  //25
		,249  //26
		,251  //27
		,253  //28
		,254  //29
		,254  //30
		,255  //31
};
		unsigned int byteRx,byteRxold;
		unsigned char changeT=0;
		unsigned int tcount=0;
		unsigned char isenu,isenun;
		//unsigned char inote=0;
		void noteformula(float note);

		void main(void)
		{
			inicio();


			while(1)	{

//				byteRx='1';

			uart_send_string("ESPERANDO");line_jump();
			}

		}

		#pragma vector=TIMER0_A0_VECTOR
		__interrupt void Timer0(void)
		{
			_BIC_SR(GIE);

			TA0CCTL0&=~CCIFG;
			TA0CTL&=~TAIFG;



			if (isenun<32)
			{
				P2OUT=senuu[isenu];
				isenu++;
				isenun++;
			}else
			{//else{isenu=0;isenun=0;}
				if((isenun>=32)&&(isenun<64))
				{
					P2OUT=senuu[isenu-1];
					isenu--;isenun++;
				}else
				{
					if((isenun>=64)&&(isenun<96))
					{
						P2OUT=255-senuu[isenu];
						isenu++;isenun++;

					}else
					{

						if((isenun>=96)&&(isenun<128))
						{
							P2OUT=256-senuu[isenu];
							isenu--;
							isenun++;
						}else
						{
							isenu=0;isenun=0;
						}

					}

				}


			}

			_BIS_SR(GIE);
		}



		#pragma vector= USCIAB0RX_VECTOR
		__interrupt void RX_vector (void)
		{
			_BIC_SR(GIE);
			IFG2&=UCA0RXIFG;
			byteRx=UCA0RXBUF;
			if(byteRx=='z'){changeT=0;}
			if(('0'<=byteRx)){changeT=1;}else{byteRx='1';}
			_BIS_SR(GIE);
		}



