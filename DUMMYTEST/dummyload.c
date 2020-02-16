#include <msp430g2553.h>
#include"CDC.h"
#include"lcd16x2.h"

volatile unsigned int TCOUNTT=75,Tcountt=0,count_t=0;
unsigned int Vmax,Vin,ViES,VES1,VES2,VES3,VES4,Vout=100;
volatile char sec_t=0,min_t=0,hour_t=0,day_t=0,I_I=0,SerOK=0,side_t='0',G_IRA='0';

char Estado[5]={'P','M','P','U','P'}; // P principal M modificando  S Stopped
char I_pos=0,	key_p1='P';
unsigned int time_b=0,v_sel=0;
unsigned int Vbat=0;
/*************************************FUNCTION DECLARATION******************************************************/
    void clk_init();
    void DACPWM();
    void init_Buttons();
    void menu();
    void menu_1();
    void menu_2();
    char read_button();
        void clk_init();
        void uart_init();
        void enable_interrupts();
        void sample_buttons();
        void ADC10_enable();
        void Timer_module();
        void read_battey();
        void enable_timer();
    /****************************************MAIN CODE**************************************************************/
	int main(void)
	{
		clk_init();
		__disable_interrupt();


		LcdInicio();
		SetCursorPosition(0, 1);
		PrintStr("Test LCD");
	 	ClearDisplay();

	 	uart_init();
		//init_Buttons();
		//sample_buttons();
		Timer_module();
		enable_timer();
		enable_interrupts();




		while(1)
		{

		/*	sample_buttons();

				switch (key_p1)
				{
				case'P':{	menu_2();}break;
				case 'M':{	menu();}break;
				case 'U':{menu_1();}break;
				}
				key_p1=read_button();
		*/
			SetCursorPosition(0, 0);
			PrintStr("Test LCD");
			SetCursorPosition(1, 0);
					Lph_ui(day_t);putme(':'); Lph_ui(hour_t);putme(':'); Lph_ui(min_t);putme(':'); Lph_ui(sec_t);//c_lc();
					p_ui(day_t);uart_write_byte(':'); p_ui(hour_t);uart_write_byte(':'); p_ui(min_t);uart_write_byte(':'); p_ui(sec_t);line_jump();
					_delay_cycles(16000000);//10000);


				//read_battey();



		}
	}




/***********************************END OF MAIN RUTINE**************************************************/

	   void enable_interrupts()
	 		{
	 			_BIS_SR(GIE);
	 			__enable_interrupt();
	 			__bis_SR_register(GIE);
	 		}

	   void clk_init()
			{
				WDTCTL = WDTPW | WDTHOLD;
				BCSCTL1 =CALBC1_16MHZ;
				BCSCTL2 =0;
				DCOCTL = CALDCO_16MHZ;
			}

	   void init_Buttons()
	 	   {
	 		     ADC10CTL0 =0;

	 		ADC10CTL1 	 = 		INCH_11|ADC10DIV_7;
	 		ADC10CTL0 	 = 		ADC10SHT_3|MSC| ADC10ON  ;
	 		ADC10AE0 	|= 		BIT5;
	 		ADC10_enable();
	     	while((ADC10CTL0&ADC10IFG) !=ADC10IFG);
	 		Vmax=ADC10MEM;


	 		VES1=1*Vmax;
	 		VES2=1.2*Vmax;
	 		VES3=1.56*Vmax;


	 	   }


	   void ADC10_enable()
		       {
			     ADC10CTL0 |= (ENC | ADC10SC);
			   }
		  void sample_buttons()
		       {
			     ADC10CTL0 =0;

			  ADC10CTL1 	 = 		INCH_5|ADC10DIV_7;
				 ADC10CTL0 	 = 		ADC10SHT_3|MSC| ADC10ON  ;
				 ADC10AE0 	= 		BIT5;

				}


	  void read_battey()
	       {
		     ADC10CTL0 =0;

		  ADC10CTL1 	 = 		INCH_4|ADC10DIV_7;
		  ADC10CTL0 	 = 		ADC10SHT_3|MSC| ADC10ON  ;
		  ADC10AE0 	= 		BIT4;
		  ADC10_enable();
			while((ADC10CTL0&ADC10IFG) !=ADC10IFG);
			Vbat=ADC10MEM;
			}





		   void menu_2()
			   {

/*
					SetCursorPosition(0, 0);
					PrintStr("Capacity Estado");

					SetCursorPosition(0, 11);
					Lp_ui(ncount);


					SetCursorPosition(1, 0);
					PrintStr("Tiempo");

					SetCursorPosition(1, 11);
					Lp_ui(ncount);

*/

			   uart_send_string("Capacidad ");p_ui((hour_t+(min_t/60))*v_sel);
			  	uart_send_string(" volts1 ");p_ui(Vbat);uart_send_string(" estado ");uart_write_byte(Estado[I_pos]);line_jump();

			   }
		   void menu_1()
		   {


			   uart_send_string("volts ");p_ui(TACCR1);
			   uart_send_string(" Amps ");p_ui(Vout);s_pc();p_ui(hour_t);s_pc();p_ui(min_t);s_pc();p_ui(sec_t);line_jump();

				/*SetCursorPosition(0, 0);
				PrintStr("Amps  ");
				SetCursorPosition(0, 11);
				Lp_ui(ncount);


				SetCursorPosition(1, 0);
				PrintStr("volt ");
				SetCursorPosition(1, 11);
				Lp_ui(ncount);
*/

		   }
			void menu()
			{

					volatile char key_p=0,TACCR1aux=TACCR1;
					TACCR1=0;
				do{


					 uart_send_string("volts ");p_ui(TACCR1aux);
							 uart_send_string(" Amps ");p_ui(Vout);s_pc();p_ui(sec_t);s_pc();p_ui(min_t);s_pc();p_ui(hour_t);line_jump();

					_delay_cycles(2000000);
					key_p=read_button();

					if (key_p=='U')
					{
						if(TACCR1aux<490){TACCR1aux+=2;}
					}
					else
					{
						if(key_p=='D')
						{
							if(TACCR1aux>2){TACCR1aux-=2;}

						}

					}

				}while(key_p!='P');
				TACCR1=TACCR1aux;

			}
			void enable_timer()
					{
					TA1CTL	 = ID_3|TASSEL_2|MC_1; //UP mode
					TA1CCR0	 = 2000;
					TA1CCTL1 =OUTMOD_7| CCIE;
					TA1CCR1=000;
					}

		   char evaluate_key()
		   {

			   if(I_pos>3){I_pos=0;}else{I_pos++;}
			   return I_pos;
		   }

		  /* char read_button()
		 	   	   {

		 	   		ADC10_enable();
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
*/
		  void uart_init()
			   {
					P1SEL |= ( BIT1|BIT2);
					P1SEL2 |= (BIT1| BIT2);
					UCA0CTL1 = UCSWRST;
					UCA0CTL1 |= UCSSEL_2;                     // SMCLK
					UCA0BR0 = 130;//65;                            // 16MHz 9600 PREESCALAR
					UCA0BR1 = 6;//3;                             //(UCAxBR0 + UCAxBR1 � 256)
					UCA0MCTL =6<<1;//UCBRS0;                        // Modulation UCBRSx = 1
					UCA0CTL1 &= ~UCSWRST;
					IE2 = UCA0RXIE;
			   }

			void Timer_module()
			{
				volatile int SerOK=0;
				P1DIR|=BIT6;
				P1SEL|=BIT6;
				P1SEL2&=~(BIT6);

		 	   TACTL	 = ID_3|TASSEL_2|MC_1;
			   TACCR0	 = 500;// Fijo para la frecuencia
			   TACCTL1 =OUTMOD_7;
			   TACCR1=50; //variable
			}

#pragma vector=TIMER1_A1_VECTOR
__interrupt void Timer1a1_isr(void)
{
	TA1CCTL1&=~CCIFG;

   if(Tcountt==0){   P2OUT|=BIT0; }
	else{if(Tcountt>TCOUNTT) {  P2OUT&=~BIT0;} }
    if(Tcountt< 100 ){   Tcountt++;    }else{   Tcountt=0;     }

    if(count_t>1000)//1000
    {
      count_t=0;

       if(sec_t>58)
		 {
		  sec_t=0;
		    if(min_t>58)
			 {

		    	min_t=0;

				if(hour_t>23)
				{
					hour_t=0;
					day_t+=1;

				}else{hour_t+=1;}

			 }else{ min_t+=1;}


		 }else{sec_t+=1;}

   }else{count_t++;}

}
