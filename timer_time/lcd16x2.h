/*
 * lcd16x2.h
 *
 *  Created on: 28/06/2016
 *      Author: Mauricio
 */

#ifndef LCD16X2_H_
#define LCD16X2_H_

#define     RS            0X02          // P2.1
#define     EN            0X08          // P2.3
#define     LCM_PIN_D7            0X80          // P2.7
#define     LCM_PIN_D6            0X40          // P2.6
#define     LCM_PIN_D5            0X20          // P2.5
#define     LCM_PIN_D4            0X10          // P2.4



  void LcdEnable()
   {
	 P2OUT&=~EN;
	 _delay_cycles(4000);//200);
	 P2OUT|=EN;
	 _delay_cycles(4000);//200);
	 P2OUT&=~EN;
	 _delay_cycles(4000);//200);
   }





  void SendByte(char ByteToSend, int IsData)
   {
	  P2OUT=0X00;

	  P2OUT|=(ByteToSend & 0xF0);


	   if(IsData==1)
	    {
	      P2OUT|=RS;
	    }
	   else
	   {
		  P2OUT&=~RS;
	   }

	   LcdEnable();

       P2OUT=0X00;

	   P2OUT=((P2OUT |(ByteToSend & 0x0F)) << 4);

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

  void lcd_init()
  {
	 P2DIR=0XFF;

	 P2OUT=0x00;

	 _delay_cycles(2000000);//100000




	 P2OUT=0X20; //d5=1;
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


 void lcd_print_uint(unsigned int intchar1)
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
