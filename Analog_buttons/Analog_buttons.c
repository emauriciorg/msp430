#include <msp430g2553.h>
#include"CDC.h"
/************************************VARIABBLE AND MACROS******************************************************/

unsigned int Vmax,Vin,RES1,RES2,RES3,RES3,RES4,ViES,VES1,VES2,VES3,VES4,Vout=100;
char Estado[3]={'P','M','P'};
char I_pos=0,	key_p1='P';
/*************************************FUNCTION DECLARATION******************************************************/

void CalButtons();
void TempSample();
    void clk();
    void uart();
    void Enin();
void menu();
void menu_1();
void menu_2();
    void ADC10setup();
    void InicioADC10();
  char read_button();
  char evaluate_key();
/****************************************MAIN CODE**************************************************************/
	int main(void)
	{
		clk();

			uart();




		CalButtons();


		ADC10setup();

		Enin();



		while(1)
		{

			if(key_p1=='P')
			{
				menu_2();
			}
			else
			{
				if(key_p1=='M'){
				menu();}
			}
			key_p1=read_button();
			_delay_cycles(2000000);


			//enviardato(read_button());s_pc();p_ui(Vin);s_pc();p_ui(Vmax);s_pc();p_ui(VES1);s_pc();p_ui(VES2);s_pc();p_ui(VES3);clc_();




		}
	}
/***********************************END OF MAIN RUTINE**************************************************/


	  void InicioADC10()
	       {
		     ADC10CTL0 |= (ENC | ADC10SC);
		   }
	  void ADC10setup()
	       {
		     ADC10CTL0 =0;

		  ADC10CTL1 	 = 		INCH_5|ADC10DIV_7;
			 ADC10CTL0 	 = 		ADC10SHT_3|MSC| ADC10ON  ;
			 ADC10AE0 	= 		BIT5;

			}
	   void CalButtons()
	   {
		     ADC10CTL0 =0;

		ADC10CTL1 	 = 		INCH_11|ADC10DIV_7;
		ADC10CTL0 	 = 		ADC10SHT_3|MSC| ADC10ON  ;
		ADC10AE0 	|= 		BIT5;
		InicioADC10();
    	while((ADC10CTL0&ADC10IFG) !=ADC10IFG);
		Vmax=ADC10MEM;


		VES1=1*Vmax;
		VES2=1.2*Vmax;
		VES3=1.56*Vmax;


	   }



	  void uart()
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


	   void Enin()
	 		{
	 			_BIS_SR(GIE);
	 			__enable_interrupt();
	 			__bis_SR_register(GIE);
	 		}
	   void clk()
			{
				WDTCTL = WDTPW | WDTHOLD;
				BCSCTL1 =CALBC1_16MHZ;
				BCSCTL2 =0;
				DCOCTL = CALDCO_16MHZ;
			}


	   void menu_2()
		   {

			 ec("menu 2 , here goes something");ec(" something else");enviardato(10);clc_();


		   }
	   void menu_1()
	   {

		 ec("menu 1,");p_ui(Vout);clc_();


	   }
		void menu()
		{
	  volatile char key_p=0;
			do{

				menu_1();
				_delay_cycles(2000000);

				key_p=read_button();
				if (key_p=='U')
				{
					Vout+=2;
				}
				else
				{
					if(key_p=='D')
					{
					Vout-=2;

					}

				}

			}while(key_p!='P');



		}

	   char evaluate_key()
	   {

		   if(I_pos>1){I_pos=0;}else{I_pos++;}
		   return I_pos;
	   }

	   char read_button()
	 	   	   {

	 	   		InicioADC10();
	 	   	    while((ADC10CTL0&ADC10IFG) !=ADC10IFG);
	 	   		Vin=ADC10MEM;
	 	   		if(Vin<900)
	 	   		{

	 				if( (Vin<(VES3+20))&&(Vin>(VES2+30)) )
	 				{
	 					return 'U';
	 				}else
	 				{
	 					if( (Vin<(VES2+20))&&(Vin>(VES1+30)) )
	 					{
	 						return 'D';
	 					}
	 					else
	 					{
	 						if( (Vin<(VES1+30)) )
	 					  {

	 						return Estado[evaluate_key()];
	 					  }

	 					}
	 				}
	 	   		}else{return  Estado[I_pos]; }

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
			case 'q':{	if(TCOUNTT<99){TCOUNTT+=1;}	}break;
			case 'a':{	if(TCOUNTT>1){TCOUNTT-=1;}	}break;
		}
	}
*/
