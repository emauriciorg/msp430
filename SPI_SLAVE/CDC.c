/*
 * CDC.c
 *
 *  Created on: 12/03/2017
 *      Author: Mauricio
 */
#include"CDC.h"
char aux_char[7];
char signo;
unsigned char _UD,_U,_D,_UM,_C,_DM;
unsigned long u,d,c,um,dm,cm,uM,dM,cM;
unsigned int auxSR=0;
volatile char UartInput=0;
void SingleChar(char dato){UCA0TXBUF = dato;while (!(IFG2&UCA0TXIFG));}

void UartConf()
{
 P1SEL |= ( BIT1|BIT2);
 P1SEL2 |= (BIT1| BIT2);
 UCA0CTL1 = UCSWRST;
 UCA0CTL1 |= UCSSEL_2;                     // SMCLK
 UCA0BR0 = 130;//65;                            // 16MHz 9600 PREESCALAR
 UCA0BR1 = 6;//3;                             //(UCAxBR0 + UCAxBR1 × 256)
 UCA0MCTL =6<<1;//UCBRS0;                        // Modulation UCBRSx = 1
 UCA0CTL1 &= ~UCSWRST;
 IE2 = UCA0RXIE;
}

int String2Int(char iamstring)
{
	unsigned int iamint=0;
	iamint=( iamstring-48)+iamint;
	return iamint;
}
void PrintStr(char *cadena)
{
	char *c;
	c = cadena;
	while ((c != 0) && (*c != 0))
	{
		SingleChar(*c);
		c++;
	}
}

int TwoC2Dec(unsigned int twoc)
{
	signo='+';
	if((twoc&0x8000)==0x8000)
	{
	twoc=(~twoc)+1;
	signo='-';
	}
	return twoc;
}

unsigned int C2UInt( char *c2uc)
{
	char *c2ucp;
	c2ucp=c2uc;
	unsigned int iamres=0;

	while((*c2ucp!=0)&&(c2ucp!=0)&&(*c2ucp!=13)){
		iamres=(iamres*10)+(*c2ucp-48);
		c2ucp++;
	}
	return iamres;
}

void SingleSpace(){SingleChar(' ');}
void ClearTerminal(){SingleChar(13);}
void LineFeed(){SingleChar(10);}
void PrintLong(unsigned long longtochar)
{
	cM=(longtochar/100000000);
	dM=((longtochar-(cM*100000000))/10000000);
	uM=(longtochar-(((dM+(cM*10))*10000000)))/1000000;
	cm=((longtochar-((uM+(dM*10)+(cM*100))*1000000))/100000);
	dm=(longtochar-((cm+(uM*10)+(dM*100)+(cM*1000))*100000))/10000;
	um=(longtochar-((dm+(cm*10)+(uM*100)+(dM*1000)+(cM*10000))*10000))/1000;
	c=(longtochar-((um+(dm*10)+(cm*100)+(uM*1000)+(dM*10000)+(cM*100000))*1000))/100;
	d=(longtochar-((c+(um*10)+(dm*100)+(cm*1000)+(uM*10000)+(dM*100000)+(cM*1000000))*100))/10;
	u=(longtochar-((d+(c*10)+(um*100)+(dm*1000)+(cm*10000)+(uM*100000)+(dM*1000000)+(cM*10000000)))*10);
	/*aux_char1[0]=(char)(cM+48);
	aux_char1[1]=(char)(dM+48);
	aux_char1[2]=(char)(uM+48);
	aux_char1[3]=(char)(cm+48);
	aux_char1[4]=(char)(dm+48);
	aux_char1[5]=(char)(um+48);
	aux_char1[6]=(char)(c+48);
	aux_char1[7]=(char)(d+48);
	aux_char1[8]=(char)(u+48);
	PrintStr(aux_char1);
*/}

void Int2Hex(unsigned int datoint)
{
	_UD=(datoint&0x000f);
	_UM=(datoint&0x00f0)>>4;
	_DM=(datoint&0x0f00)>>8;
	_D=(datoint&0xf000)>>12;

	if(_UD<=9){_UD=_UD+48;}else{_UD=_UD+55;}
	if(_UM<=9){_UM=_UM+48;}else{_UM=_UM+55;}
	if(_DM<=9){_DM=_DM+48;}else{_DM=_DM+55;}
	if(_D<=9){_D=_D+48;}else{_D=_D+55;}
	aux_char[4]=(char)(_UD);
	aux_char[3]=(char)(_UM);
	aux_char[2]=(char)(_DM);
	aux_char[1]=(char)(_D);
	PrintStr(aux_char);
}
void PrintInt( int intchar1)
{
unsigned int intchar2=(unsigned int)(intchar1);
//	if(intchar<0){aux_char[0]='-'; intchar=intchar*(-1);}else{aux_char[0]='0';}
	_DM=(intchar2/10000);
	_UM=((intchar2-(_DM*10000))/1000);
	_C=((intchar2-((_UM*1000)+(_DM*10000)))/100);
	_D=((intchar2-((_UM*1000)+(_C*100)+(_DM*10000)))/10);
	_U=(intchar2-(_D*10+(_UM*1000)+(_C*100)+(_DM*10000)));
    /*modify this part to avoid double
     * assignation ant convert in ans send in
	few lines even avoid extra variables
	*/
	aux_char[1]=(char)(_DM+48);

	aux_char[2]=(char)(_UM+48);
	aux_char[3]=(char)(_C+48);
	aux_char[4]=(char)(_D+48);
	aux_char[5]=(char)(_U+48);
	PrintStr(aux_char);
}

void PrintUInt(unsigned int intchar1)
{
	_DM=(intchar1/10000);
	_UM=((intchar1-(_DM*10000))/1000);
	_C=((intchar1-((_UM*1000)+(_DM*10000)))/100);
	_D=((intchar1-((_UM*1000)+(_C*100)+(_DM*10000)))/10);
	_U=(intchar1-(_D*10+(_UM*1000)+(_C*100)+(_DM*10000)));
 /*look up printint and modify this*/
	aux_char[1]=(char)(_DM+48);
	aux_char[2]=(char)(_UM+48);
	aux_char[3]=(char)(_C+48);
	aux_char[4]=(char)(_D+48);
	aux_char[5]=(char)(_U+48);
	aux_char[0]=48;
	PrintStr(aux_char);
}

void PrintFloat(float twoto3)
{
	_UM=(unsigned int)(twoto3);
	_UD=(unsigned int)((twoto3-_UM)*100);
	_C=(_UM/100);
	_D=((_UM-(_C*100)))/10;
	_U=(_UM-((_C*100)+(_D*10)));
	aux_char[0]=(char)(_C+48);
	aux_char[1]=(char)(_D+48);
	aux_char[2]=(char)(_U+48);
	_D=(_UD/10);
	_U=(_UD-(_D*10));
	aux_char[3]=46;
	aux_char[4]=(char)(_D+48);
	aux_char[5]=(char)(_U+48);
	PrintStr(aux_char);
}

void PrintMenu()
{
	PrintStr("1-ReadPayload");LineFeed();ClearTerminal();
	PrintStr("2-r CONF");LineFeed();ClearTerminal();
	PrintStr("3-print");LineFeed();ClearTerminal();
	PrintStr("4-Conti Tx");LineFeed();ClearTerminal();

}
#pragma vector=USCIAB0RX_VECTOR
__interrupt void RxUartIsr(void)
{
	UartInput=UCA0RXBUF;
}



