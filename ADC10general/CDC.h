/*
 * CDC._UD=(datoint&0x000f);h
 *
 *  Created on: 18/10/2014
 *      Author: mauricio
 *
 *      CDC is an acronym for Communication and Data Converter
 *      This library contains the functions necessary to handle in a easy way the
 *      transfer of data(char strings, decimal numer, hexadecimal, special character,etc.) in
 *      uart_init-mode, basically this library transform your int, unsigned int or  float in a
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
char aux_char[7];
char aux_char1[10];
char soyunvector[];
unsigned char i;
unsigned char entero;
unsigned char _UD,_U,_D,_UM,_C,_DM;
unsigned long u,d,c,um,dm,cm,uM,dM,cM;
unsigned int auxSR=0;
unsigned int dataSR1=0;
unsigned int dataSR2=0;
unsigned  char iSR=0;

void uart_write_byte(char dato){UCA0TXBUF = dato;while (!(IFG2&UCA0TXIFG));}

int string2int(char iamstring)
{
	unsigned int iamint=0;
	iamint=( iamstring-48)+iamint;
	return iamint;
}

void readint(unsigned int dataSR){	if(iSR==5){iSR=0;  dataSR2=dataSR1;CCR0=dataSR2;dataSR1=0;TACCTL0|=CCIE;	TACTL|=TAIE;}else{dataSR1= (dataSR-48)+(dataSR1*10);iSR++;}}

void uart_send_string(char *string)
{
	char *c;
	c = string;
	while ((c != 0) && (*c != 0))
	{
		uart_write_byte(*c);
		c++;
	}
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

void espacio(){uart_write_byte(' ');}



void line_jump(){uart_write_byte(13);}

void printint(int intchar)
{
	if(intchar<0){aux_char[0]='-'; intchar=intchar*(-1);}else{aux_char[0]='0';}
	_DM=(intchar/10000);
	_UM=((intchar-(_DM*10000))/1000);
	_C=((intchar-((_UM*1000)+(_DM*10000)))/100);
	_D=((intchar-((_UM*1000)+(_C*100)+(_DM*10000)))/10);
	_U=(intchar-(_D*10+(_UM*1000)+(_C*100)+(_DM*10000)));

	aux_char[1]=(char)(_DM+48);
	aux_char[2]=(char)(_UM+48);
	aux_char[3]=(char)(_C+48);
	aux_char[4]=(char)(_D+48);
	aux_char[5]=(char)(_U+48);
	uart_send_string(aux_char);
}

void printint2c(unsigned int int2cchar)
{
	if(int2cchar==0){int2cchar=0;}else{int2cchar=~(int2cchar-1);}

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
	uart_send_string(aux_char);
}


void print_uint(unsigned int intchar1)
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
	uart_send_string(aux_char);
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
	uart_send_string(aux_char);
}

#endif /* CDC_H_ */
