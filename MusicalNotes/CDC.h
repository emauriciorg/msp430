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
char aux_char[7];
char udcm[7];
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

void ec(char *cadena)
{
	char *c;
	c = cadena;
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

void borrar(){uart_write_byte(13);}

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
	ec(aux_char);
}


void newPrint(unsigned int datta){


	if((60000&datta)==60000){udcm[1]='6';datta=datta-60000;}else{
	if((50000&datta)==50000){udcm[1]='5';datta=datta-50000;}else{
	if((40000&datta)==40000){udcm[1]='4';datta=datta-40000;}else{
	if((30000&datta)==30000){udcm[1]='3';datta=datta-30000; }else{
	if((20000&datta)==20000){udcm[1]='2';datta=datta-20000; }else{
	if((10000&datta)==10000){udcm[1]='1';datta=datta-10000; }else{
	                udcm[1]='0';
	}}}}}}

	/*


	if(0xEA60&datta){udcm[0]='6';datta=datta-0xEA60;}else{
	if(0xC350&datta){udcm[0]='5';datta=datta-0XC350;}else{
	if(0x9C40&datta){udcm[0]='4';datta=datta-0X9C40;}else{
	if(0x7530&datta){udcm[0]='3';datta=datta-0X7530; }else{
	if(0x4E20&datta){udcm[0]='2';datta=datta-0X4E20; }else{
	if(0x2710&datta){udcm[0]='1';datta=datta-0x2710; }
	}}}}}



	 if(0x03E8&datta){udcm[1]='6';datta=datta-0xEA60;}else{
	if(0x07D0&datta){udcm[1]='5';datta=datta-0XC350;}else{
	if(0x0BB8&datta){udcm[1]='4';datta=datta-0X9C40;}else{
	if(0x0FA0&datta){udcm[1]='3';datta=datta-0X7530; }else{
	if(0x1388&datta){udcm[1]='2';datta=datta-0X4E20; }else{
	if(0x1770&datta){udcm[1]='1';datta=datta-0x2710; }else{
	if(0X1B58&datta){udcm[1]='1';datta=datta-0x2710;}else{
	if(0x1F40&datta){udcm[1]='1';datta=datta-0x2710;}else{
	if(0x2328&datta){udcm[1]='1';datta=datta-0x2710;}

	}
	}
	}}}}}}

*/
		if((9000&datta)==9000){udcm[2]='9';datta=datta-9000;}else{
		if((8000&datta)==8000){udcm[2]='8';datta=datta-8000;}else{
		if((7000&datta)==7000){udcm[2]='7';datta=datta-7000;}else{
		if((6000&datta)==6000){udcm[2]='6';datta=datta-6000 ;}else{
		if((5000&datta)==5000){udcm[2]='5';datta=datta-5000;}else{
		if((4000&datta)==4000){udcm[2]='4';datta=datta-4000;}else{
		if((3000&datta)==3000){udcm[2]='3';datta=datta-3000;}else{
		if((2000&datta)==2000){udcm[2]='2';datta=datta-2000;}else{
		if((1000&datta)==1000){udcm[2]='1';datta=datta-1000;}else{
	 	                                           udcm[2]='0';
		}}}}}}}}}


		        if((900&datta)==900){udcm[3]='9';datta=datta-900;}else{
				if((800&datta)==800){udcm[3]='8';datta=datta-800;}else{
				if((700&datta)==700){udcm[3]='7';datta=datta-700;}else{
				if((600&datta)==600){udcm[3]='6';datta=datta-600 ;}else{
				if((500&datta)==500){udcm[3]='5';datta=datta-500;}else{
				if((400&datta)==400){udcm[3]='4';datta=datta-400;}else{
				if((300&datta)==300){udcm[3]='3';datta=datta-300;}else{
				if((200&datta)==200){udcm[3]='2';datta=datta-200;}else{
				if((100&datta)==100){udcm[3]='1';datta=datta-100;}else{
				              udcm[3]='0';
				}}}}}}}}}


		        if((90&datta)==90){udcm[4]='9';datta=datta-90;}else{
				if((80&datta)==80){udcm[4]='8';datta=datta-80;}else{
				if((70&datta)==70){udcm[4]='7';datta=datta-70;}else{
				if((60&datta)==60){udcm[4]='6';datta=datta-60;}else{
				if((50&datta)==50){udcm[4]='5';datta=datta-50;}else{
				if((40&datta)==40){udcm[4]='4';datta=datta-40;}else{
				if((30&datta)==30){udcm[4]='3';datta=datta-30;}else{
				if((20&datta)==20){udcm[4]='2';datta=datta-20;}else{
				if((10&datta)==10){udcm[4]='1';datta=datta-10;}else{
				             udcm[4]='0';
				}}}}}}}}}


		        if((9&datta)==9){udcm[5]='9';datta=datta-9;}else{
				if((8&datta)==8){udcm[5]='8';datta=datta-8;}else{
				if((7&datta)==7){udcm[5]='7';datta=datta-7;}else{
				if((6&datta)==6){udcm[5]='6';datta=datta-6;}else{
				if((5&datta)==5){udcm[5]='5';datta=datta-5;}else{
				if((4&datta)==4){udcm[5]='4';datta=datta-4;}else{
				if((3&datta)==3){udcm[5]='3';datta=datta-3;}else{
				if((2&datta)==2){udcm[5]='2';datta=datta-2;}else{
				if((1&datta)==1){udcm[5]='1';datta=datta-1;}else{
				            udcm[5]='0';
				}}}}}}}}}


	udcm[0]=48;
	ec(udcm);

}


void printuint(unsigned int intchar1)
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
