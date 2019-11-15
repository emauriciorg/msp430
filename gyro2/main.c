#include <msp430.h>
#include "FBF.h"
#include "GYRO.h"
#include"../commom/CDC.h"
#include <math.h>

unsigned int T1,T2,T3;
char signo ='p';
unsigned char ifgt,count=0;
unsigned int registro1;
unsigned int GZH,GZL,GAL,GAH;
int DCOS;
unsigned int nT=0;
int GZ1,GZ2,GZ,anguloAproxX,anguloAproxY,anguloAproxZ,GX1,GX2,GY1,GY2;


void setGyro();
int DCoffset();
int angle(int);


int main(void)
{
	inicio();
	inicioADC();
	i2cmaster();
	Enableinterrupts();
	setGyro();
	//registro1=gr(CTRL_REG1);
	while (1)
	{
		GZ += (GZ2 + GZ1) / 2000;
		if(GZ >= 360)
		{
			GZ -= 360;
		}
		else {
			if( GZ < 0 )
			{
				GZ += 360;
			}
		}


		ec(" X: ");printuint(twoc2dec(GX1));espacio();printuint(twoc2dec(anguloAproxX));espacio();enviardato(signo);
		ec(" Y: ");printuint(twoc2dec(GY1));espacio();printuint(twoc2dec(anguloAproxY));espacio();enviardato(signo);
		ec(" Z: ");printuint(twoc2dec(GZ1));espacio();printuint(twoc2dec(anguloAproxZ));espacio();enviardato(signo);borrar();
		ec("REG1 es ");printuint((registro1+'0'));borrar();
	}
}


int angle(int angle) /*Funcion angle return the actual angle and corrects the data*/
{
	if(angle<360)
	{
		angle-=360;
	}else
	if(angle>360)
	{
		angle+=360;
	}

	return angle;
}

int DCoffset(void)/*This function determines how much noise is on the gyro,set once at start*/
{
	int DCe,eer=0;
	for(DCe=0; DCe <= 100; DCe++)
	{
		GZL = gr(OUT_Z_L );
		GZH = gr(OUT_Z_H );
		GZ  = (GZH<<8)|GZL;
		eer = eer+GZ;
	}
	eer = eer/100;
	return eer;
}


void setGyro(void)
{
	gw(CTRL_REG1,0X0F);
	gw(CTRL_REG2,0X20);
	gw(CTRL_REG4,0X30);
}


#pragma vector = USCIAB0TX_VECTOR
__interrupt void USCIAB0TX_ISR(void)
{
//if(UCB0RXIFG&IFG2){IFG2 &= ~UCB0RXIFG;	RXData = UCB0RXBUF;}
//if(UCB0TXIFG&IFG2){IFG2 &= ~UCB0TXIFG;	 UCB0TXBUF=TXDATAI2C;}
}


#pragma vector = USCIAB0RX_VECTOR
__interrupt void USCIAB0RX_ISR(void)
{

}


#pragma vector =ADC10_VECTOR
__interrupt void ADC10VECTOR(void)
{
	ADC10CTL0&=~ADC10IFG;
	_BIC_SR(GIE);
	_BIS_SR(GIE);
}


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
