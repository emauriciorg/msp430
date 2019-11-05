/*
 * CDC._UD=(datoint&0x000f);h
 *
 *  Created on: 18/10/2014
 *      Author: mauricio
 *
 *      CDC is an acronym for Communication and Data Converter
 *      This library contains the functions necessary to handle in a easy way the
 *      transfer of data(char strings, decimal numer, hexadecimal, special character,etc.) in
 *      uart-mode, basically this library transform your int, unsigned int or  float in a
 *      string of char type variable, and send it for you.
 *
 *------------------------------FUNCTIONS-----------------------------
 *ESPACIO();
 *BORRAR();
 *
 *
 *
 *
 */
#ifndef CDC_H_
#define CDC_H_
/*Function List
 *
 * borrar();
 * espacio();
 * c2ui();
 * ec();
 * enviardato();
 * int2hex();
 * printchar2c();
 * printfloar();
 * printlong();
 * printuint();
 * readint();
 * twoc2dec();
 * string2int();
 *
 * */
char aux_char[7];
char aux_char1[10];
char soyunvector[];


 char signo;
unsigned char _UD,_U,_D,_UM,_C,_DM;
unsigned long u,d,c,um,dm,cm,uM,dM,cM;
unsigned int auxSR=0;
unsigned int dataSR1=0;
unsigned int dataSR2=0;
unsigned  char iSR=0;

void enviardato(char dato){UCA0TXBUF = dato;while (!(IFG2&UCA0TXIFG));}

int string2int(char iamstring)
{
	unsigned int iamint=0;
	iamint=( iamstring-48)+iamint;
	return iamint;
}

void readint(unsigned int dataSR){	if(iSR==5){iSR=0;  dataSR2=dataSR1;CCR0=dataSR2;dataSR1=0;TACCTL0|=CCIE;	TACTL|=TAIE;}else{dataSR1= (dataSR-48)+(dataSR1*10);iSR++;}}



void ec(char *cadena)
{
	char *c;
	c = cadena;
	while ((c != 0) && (*c != 0))
	{
		enviardato(*c);
		c++;
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


unsigned int c2ui( char *c2uc){
	char *c2ucp;
	c2ucp=c2uc;
	unsigned int iamres=0;

	while((*c2ucp!=0)&&(c2ucp!=0)&&(*c2ucp!=13)){
		iamres=(iamres*10)+(*c2ucp-48);
		c2ucp++;
	}
	return iamres;
}

void s_pc(){enviardato(' ');}

void printlong(unsigned long longtochar)
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

	aux_char1[0]=(char)(cM+48);
	aux_char1[1]=(char)(dM+48);
	aux_char1[2]=(char)(uM+48);
	aux_char1[3]=(char)(cm+48);
	aux_char1[4]=(char)(dm+48);
	aux_char1[5]=(char)(um+48);
	aux_char1[6]=(char)(c+48);
	aux_char1[7]=(char)(d+48);
	aux_char1[8]=(char)(u+48);

	ec(aux_char1);

	aux_char1[0]=8;
	aux_char1[1]=48;
	aux_char1[2]=48;
	aux_char1[3]=48;
	aux_char1[4]=48;
	aux_char1[5]=48;
	aux_char1[6]=48;
	aux_char1[7]=48;
	aux_char1[8]=48;
}

void int2hex(unsigned int datoint)
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
	ec(aux_char);
}

void clc_(){enviardato(13);}

void printint( int intchar1)
{
unsigned int intchar2=(unsigned int)(intchar1);
//	if(intchar<0){aux_char[0]='-'; intchar=intchar*(-1);}else{aux_char[0]='0';}
	_DM=(intchar2/10000);
	_UM=((intchar2-(_DM*10000))/1000);
	_C=((intchar2-((_UM*1000)+(_DM*10000)))/100);
	_D=((intchar2-((_UM*1000)+(_C*100)+(_DM*10000)))/10);
	_U=(intchar2-(_D*10+(_UM*1000)+(_C*100)+(_DM*10000)));

	aux_char[1]=(char)(_DM+48);
	aux_char[2]=(char)(_UM+48);
	aux_char[3]=(char)(_C+48);
	aux_char[4]=(char)(_D+48);
	aux_char[5]=(char)(_U+48);
	ec(aux_char);
}

void printchar2c(unsigned int int2cchar)
{


	int2cchar=(~(int2cchar))+0x01;
	_DM=(int2cchar/10000);
	_UM=((int2cchar-(_DM*10000))/1000);
	_C=((int2cchar-((_UM*1000)+(_DM*10000)))/100);
	_D=((int2cchar-((_UM*1000)+(_C*100)+(_DM*10000)))/10);
	_U=(int2cchar-(_D*10+(_UM*1000)+(_C*100)+(_DM*10000)));

	aux_char[1]=(char)(_DM+48);
	aux_char[2]=(char)(_UM+48);
	aux_char[3]=(char)(_C+48);
	aux_char[4]=(char)(_D+48);
	aux_char[5]=(char)(_U+48);
	ec(aux_char);
}


void p_ui(unsigned int intchar1)
{
	_DM=(intchar1/10000);
	_UM=((intchar1-(_DM*10000))/1000);
	_C=((intchar1-((_UM*1000)+(_DM*10000)))/100);
	_D=((intchar1-((_UM*1000)+(_C*100)+(_DM*10000)))/10);
	_U=(intchar1-(_D*10+(_UM*1000)+(_C*100)+(_DM*10000)));

	aux_char[1]=(char)(_DM+48);
	aux_char[2]=(char)(_UM+48);
	aux_char[3]=(char)(_C+48);
	aux_char[4]=(char)(_D+48);
	aux_char[5]=(char)(_U+48);
	aux_char[0]=48;
	ec(aux_char);
}

void printfloat(float twoto3)
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
	ec(aux_char);
}

#endif /* CDC_H_ */
