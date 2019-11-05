/*
 * lcd16x2.h
 *
 *  Created on: 28/06/2016
 *      Author: Mauricio
 */

#ifndef LCD16X2_H_
#define LCD16X2_H_

#define     RS            BIT4          // P2.1           P2.4
#define     EN            BIT5          // P2.3           P2.5
#define     L_D5          BIT7          // P2.5    P1.7
#define     L_D4          BIT6          // P2.4    P1.6
#define     L_D7          BIT6          // P2.7 --P2.6
#define     L_D6          BIT7          // P2.6   P2.7
volatile char  lauxdata=0,HIGHNIBLE=0,LOWNIBLE=0;


  void LcdEnable()
   {
	 P2OUT&=~EN;
	 _delay_cycles(500);//200);
	 P2OUT|=EN;
	 _delay_cycles(500);//200);
	 P2OUT&=~EN;
	 _delay_cycles(500);//200);
   }





  void SendByte(char ByteToSend, int IsData)
   {
	  // B P2OUT&=~(L_D6|L_D4  |L_D5  |L_D7|RS|EN  ); //full zero

	   P2OUT&=~(L_D6  |L_D7|RS|EN  ); //full zero
	   P1OUT&=~(L_D4  |L_D5);

	   HIGHNIBLE=(ByteToSend & 0xF0);
       lauxdata=((HIGHNIBLE&BIT6)<<1)|((HIGHNIBLE&BIT7)>>1);
	   P2OUT|=lauxdata;

	    lauxdata=((HIGHNIBLE&BIT5)<<2)|((HIGHNIBLE&BIT4)<<2);
	   	P1OUT|=lauxdata;


	   //bP2OUT|=(ByteToSend & 0xF0);



	  //Asignacion

	  //P2OUT|=(D1|D3|D5)&HIGHNIBLE

	   if(IsData==1)
	    {
	      P2OUT|=RS;
	    }
	   else
	   {
		  P2OUT&=~RS;
	   }

	   LcdEnable();

	  //B P2OUT&=~(L_D4  |L_D5  |L_D6  |L_D7|RS|EN  ); //full zero

	  //B P2OUT|=((P2OUT |(ByteToSend & 0x0F)) << 4); ///not or

	   P2OUT&=~(L_D6  |L_D7|RS|EN  ); //full zero
	   	   P1OUT&=~(L_D4  |L_D5);

	   	 LOWNIBLE=((ByteToSend & 0x0F)<<4);
	   	 lauxdata=((LOWNIBLE&BIT6)<<1)|((LOWNIBLE&BIT7)>>1);
	   	 P2OUT|=lauxdata;

	   	 lauxdata=((LOWNIBLE&BIT5)<<2)|((LOWNIBLE&BIT4)<<2);
	   	P1OUT|=lauxdata;


	   //P2OUT=P2OUT|DATO&(LOW NIBLE) AND SHIFT

	   if(IsData==1)
	  	    {
	  		  P2OUT|=RS;
	  	    }
	  	   else
	  	   {
	  		  P2OUT&=~RS;
	  	   }
	   LcdEnable();
    }


void Ls_pc(){SendByte((' '),1);}
void putme(char putme){SendByte((putme),1);}

  void LcdInicio()
  {


	  P1OUT&=~(L_D4|L_D5);
	  P2OUT&=~(RS|EN|L_D6|L_D7);
	 P2SEL&=~(RS|EN|L_D6|L_D7);
	 P2SEL2&=~(RS|EN|L_D6|L_D7);
	 P2DIR|=(RS|EN|L_D6|L_D7);
	 P2OUT&=~(RS|EN|L_D6|L_D7);
 	 P1SEL&=~(L_D4|L_D5);
 	 P1SEL2&=~(L_D4|L_D5);
 	 P1OUT&=~(L_D4|L_D5);
	 P1DIR|=(L_D4|L_D5);


	 _delay_cycles(2000000);//100000




	 // BP2OUT|=L_D5;
	 P1OUT|=L_D5;
	 LcdEnable();

SendByte(0x28,0);

   //
// 2. Display on, cursor on, blink cursor
   //
 SendByte(0x0E,0);

   //
 //  3. Cursor move auto-increment
   //
   SendByte(0x06, 0);
  }


 void ClearDisplay()
  {
 SendByte(0x01, 0);
	     SendByte(0x02, 0);
  }


 void SetCursorPosition(char Row, char Col)
 {
     char address;
     //
     // construct address from (Row, Col) pair
     //

     if (Row == 0)
     {
         address = 0;
     }
     else
     {
         address = 0x40;
     }

     address |= Col;
     SendByte(0x80 | address,0);
 }







 void PrintStr(char *Text)
 {
     char *c;
     c = Text;

     while ((c != 0) && (*c != 0))
     {
         SendByte(*c,1);
         c++;
     }
 }


 void Lph_ui(unsigned int intchar1)
 {

 	_D=(intchar1/10);
 	_U=(intchar1-(_D*10));


 	SendByte(((char)(_D+48)),1);

 	SendByte(((char)(_U+48)),1);

 }

 void Lp_ui(unsigned int intchar1)
 {
 	_DM=(intchar1/10000);
 	_UM=((intchar1-(_DM*10000))/1000);
 	_C=((intchar1-((_UM*1000)+(_DM*10000)))/100);
 	_D=((intchar1-((_UM*1000)+(_C*100)+(_DM*10000)))/10);
 	_U=(intchar1-(_D*10+(_UM*1000)+(_C*100)+(_DM*10000)));

 	SendByte((char)(_DM+48),1);
	SendByte((char)(_UM+48),1);
 	SendByte((char)(_C+48),1);
 	SendByte((char)(_D+48),1);
 	SendByte((char)(_U+48),1);
 //	SendByte('0',1);

 }







#endif /* LCD16X2_H_ */
