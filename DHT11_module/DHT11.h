/*
 * DHT11.h
 *
 *  Created on: 08/09/2016
 *      Author: Mauricio
 */

#ifndef DHT11_H_
#define DHT11_H_

#define DHT11   BIT0 //sensor pin 1-wire OW

char byte0=0,byte1=0,byte2=0,byte3=0,byte4=0,bytex=0,Timeout=0;

volatile int checksum,DataRH,DataRHd,DataT,DataTd, err_dht,NDATA,checksum;
volatile int countt1=0,SerOK1=0,countd11=0,Ndata1=0;
volatile char Temp1=0, Hum1=0,Tempd=0,HumD=0;
volatile char changee=0;



   void request18()
   {

	   //REQUEST
	P1DIR|=(BIT0);
	P1OUT|=BIT0;
	delay_millis(5);
	P1OUT&=~BIT0;
	delay_millis(15);//18 millis
	P1OUT|=BIT0;


	TACTL	 = ID_2|TASSEL_2|MC_1;
		TACCR0	 =88; //
		TACCTL0 =OUTMOD_7;
		TACCR1=0;
		TACCTL0&=~CCIFG;
	 while((TACCTL0&CCIFG)!=CCIFG);
		 TACCTL0&=~CCIFG;
	TACCTL0|=TACLR;


	P1DIR&=~(BIT0);
// RESPONSE
	TACTL	 = ID_2|TASSEL_2|MC_1;
	TACCR0	 = 490; // xxx (54)+ yyy(80us);
	TACCTL0 =OUTMOD_7;
	TACCR1=0;
	TACCTL0&=~CCIFG;
	 while((TACCTL0&CCIFG)!=CCIFG);
	TACCTL0&=~CCIFG;
	TACCTL0|=TACLR;

	P1DIR&=~(BIT0); //p1.0 as input, ready to read
// END RESPONSE

   }


   void endOfFrame()
   {


		TACTL	 = ID_2|TASSEL_2|MC_1;
		TACCR0	 = 536; // 216 (54)+ 320(80us);
		TACCTL0 =OUTMOD_7;
		TACCR1=0;
		TACCTL0&=~CCIFG;
		 while((TACCTL0&CCIFG)!=CCIFG);
		TACCTL0&=~CCIFG;
		TACCTL0|=TACLR;


   }

   	   void DTH11_data()
   	   {

      volatile int countd1=0;

        P1DIR|=(BIT0);
   		P1OUT|=BIT0;
   		delay_millis(5);//14
   		P1OUT&=~BIT0;
   		delay_millis(15);//18 millis
   		P1OUT|=BIT0;

   		TACTL	 = ID_2|TASSEL_2|MC_1;
   			TACCR0	 =160; // 40us 160
   			TACCTL0 =OUTMOD_7;
   			TACCR1=0;
   			TACCTL0&=~CCIFG;
   		 while((TACCTL0&CCIFG)!=CCIFG);
   			 TACCTL0&=~CCIFG;
   		TACCTL0|=TACLR;


   		P1DIR&=~(BIT0);
   	// RESPONSE
   		TACTL	 = ID_2|TASSEL_2|MC_1;
   		TACCR0	 = 624; // 216 (54)+ 320(80us);
   		TACCTL0 =OUTMOD_7;
   		TACCR1=0;
   		TACCTL0&=~CCIFG;
   		 while((TACCTL0&CCIFG)!=CCIFG);
   		TACCTL0&=~CCIFG;
   		TACCTL0|=TACLR;

   		P1DIR&=~(BIT0);
   	// END RESPONSE


////
   		   Timeout=0;
	      Ndata1=0;
	      countt1=0;

	 	   TACTL	 = ID_1|TASSEL_2|MC_1;
		   TACCR0	 = 8;
		   TACCTL0 =OUTMOD_7;
		   TACCR1=0;
		   TACCTL0&=~CCIFG;

		   while((Ndata1<40)&&(Timeout!=1))
			{
			   while(((P1IN&DHT11)==0));//54us


			  while((countd1<80)&&((P1IN&DHT11)==1))
			  {

					  while((TACCTL0&CCIFG)!=CCIFG);
					  TACCTL0&=~CCIFG;

					  countd1++;
			  }

			  if(countd1>30)
			  {

				  byte0=(byte0<<1)|((byte1>>7)&BIT0);
				  byte1=(byte1<<1)|((byte2>>7)&BIT0);
				  byte2=(byte2<<1)|((byte3>>7)&BIT0);
				  byte3=(byte3<<1)|((byte4>>7)&BIT0);
				  byte4=(byte4<<1)|0X01;
			  }else
			  {

				  byte0=(byte0<<1)|((byte1>>7)&BIT0);
				  byte1=(byte1<<1)|((byte2>>7)&BIT0);
				  byte2=(byte2<<1)|((byte3>>7)&BIT0);
				  byte3=(byte3<<1)|((byte4>>7)&BIT0);
				 byte4=(byte4<<1) & 0xFE;
			   }

			  countd1=0;
			  Ndata1++;
			}//end of while 40 bits
				TACCTL0|=TACLR;
			}



#endif /* DHT11_H_ */
