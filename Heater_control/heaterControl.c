#include <msp430g2553.h>
#include"CDC.h"
#include"lcd16x2.h"
/************************************VARIABBLE AND MACROS******************************************************/
volatile char DES=0,flag11;
volatile char sec_t=0,min_t=0,hour_t=0,day_t=0,I_I=0,SerOK=0,side_t='0',G_IRA='0';
volatile unsigned int COUNTT=75,countt=0,count_t=0;
volatile unsigned int TCOUNTT=100,Tcountt=0,Tcount_t=0;


unsigned int	TempVolt[8]={0};
unsigned int 	TempC[7]={0};
unsigned int 	TempCA[5]={0};
/*************************************FUNCTION DECLARATION******************************************************/
    void TempSample();
    void clk_init();
    void uart_init();
    void enable_timer();
    void enable_interrupts();
    void sermotor();
    void timer0_en();
    void ADC10setup();
    void controlTemp(unsigned int);
    void ADC10_enable();
	void servoCheck();
	void showLCD();
	void girar(char);
/****************************************MAIN CODE**************************************************************/
	int main(void)
	{
		clk_init();

	    P2SEL2&=~(BIT1|BIT2);
		P2SEL&=~(BIT1|BIT2);
		P2DIR|=(BIT1|BIT2);
		P2OUT&=~(BIT1|BIT2);

	 	   TACTL	 = ID_3|TASSEL_2|MC_1; //UP mode
		   TACCR0	 = 40;
		   TACCTL0 =OUTMOD_7;
		   TACCR1=0;
		 	enable_interrupts();

		 do{

			while((TACCTL0&CCIFG)!=CCIFG);

			TACCTL0&=~CCIFG;

			if(countt<76){P2OUT|=BIT1;}else{P2OUT&=~BIT1;}
			if(countt<1001){countt++;}else{countt=0;SerOK++;}



		 }while(SerOK!=10);

		 countt=0;
			TACCTL0|=TACLR;
			G_IRA=0;
			SerOK=0;
			__disable_interrupt();



		LcdInicio();
	 	ClearDisplay();

		SetCursorPosition(0, 0);

	 	PrintStr("inicio ");




			P1DIR|=(BIT4);
			P1SEL&=~(BIT4);
			P1SEL2&=~(BIT4);

		//	uart_init();

		ADC10setup();

		enable_timer();

	 	TempCA[3]=35;

	 	enable_interrupts();
		while(1)
		{

		TempSample();

		controlTemp(TempC[6]);



	    servoCheck();

	    showLCD();

      _delay_cycles(4000000);




		}
	}
/***********************************END OF MAIN RUTINE**************************************************/
	void girar(char SIDE_T )
			{
				if(I_I==1)
				{
					I_I=0;
					switch(SIDE_T)
					{
					case'R':if(COUNTT<92){COUNTT++;}else{SerOK=18;}break;
					case'L':if(COUNTT>65){COUNTT--;}else{SerOK=18;};break;
					case'Z':COUNTT=76;SerOK++;break;

					}

			   }else{I_I=1;}
			}
	 void timer0_en()
	      {

	 	   TACTL	 = ID_3|TASSEL_2|MC_1; //UP mode
		   TACCR0	 = 40;
		   TACCTL0 =OUTMOD_7;
		   TACCR1=0;

	      }
	 void showLCD()
   		   {
   			SetCursorPosition(0, 0);
   			PrintStr("Temp ");
   			Lph_ui(TempCA[3]);putme(' ');putme(side_t); putme(' '); Lp_ui(TempC[6]);
   			SetCursorPosition(2, 0);
   			Lph_ui(day_t);putme(':'); Lph_ui(hour_t);putme(':'); Lph_ui(min_t);putme(':'); Lph_ui(sec_t);//c_lc();

   		   }
   	void servoCheck()
   			{
				if(G_IRA==1)
				{
						 timer0_en();
				 do{

					while((TACCTL0&CCIFG)!=CCIFG);

					TACCTL0&=~CCIFG;

					if(countt<COUNTT){P2OUT|=BIT1;}else{P2OUT&=~BIT1;}
					if(countt<1001){countt++;}else{countt=0;girar(side_t);}



				 }while(SerOK!=18);


				countt=0;
				TACCTL0|=TACLR;
				G_IRA=0;
				SerOK=0;

		}

   			}
	void enable_timer()
			{
			TA1CTL	 = ID_3|TASSEL_2|MC_1; //UP mode
			TA1CCR0	 = 2000;
			TA1CCTL1 =OUTMOD_7| CCIE;
			TA1CCR1=000;
			}

	  void ADC10_enable()
	       {
		     ADC10CTL0 |= (ENC | ADC10SC);
		   }
	  void ADC10setup()
	       {
		  	 ADC10CTL1 	 = 		INCH_0|ADC10DIV_7;
			 ADC10CTL0 	 = 		ADC10SHT_3|MSC| ADC10ON  ;
			 ADC10AE0 	|= 		BIT0;

			}

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


	  void controlTemp(unsigned int TempC)
			{
				 if(TempC<375){	        P1OUT|=BIT4; TCOUNTT=16;  }
				 else{
				     // if(TempC>375){
					 P1OUT&=~BIT4;  TCOUNTT=100;   }
				   // }
			}





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

	   void TempSample()
	   {
		   	ADC10_enable();
			while((ADC10CTL0&ADC10IFG) !=ADC10IFG);
			TempVolt[0]=ADC10MEM;
			ADC10CTL0&=~ADC10IFG;

	   	    TempVolt[4]=TempVolt[3];
	   	    TempVolt[3]=TempVolt[2];
	   	    TempVolt[2]=TempVolt[1];
	   		TempVolt[1]=TempVolt[0];
	   		TempVolt[5]=(TempVolt[1]+TempVolt[2]+TempVolt[3]+TempVolt[4])/4;
	   			//function to shown temperature;
			TempC[5]=TempC[4];
			TempC[4]=TempC[3];
			TempC[3]=TempC[2];
			TempC[2]=TempC[1];
			TempC[1]=TempC[0];
			_delay_cycles(100);
			TempC[0]=(((TempVolt[5]*5.46)-678.4));
			TempC[6]=(TempC[1]+TempC[2]+TempC[3]+TempC[4]+TempC[5]+TempC[6])/6;

			TempCA[0]=TempC[6]/10;

			TempCA[1]=TempCA[0]*10;

			TempCA[2]=TempC[6]-TempCA[1];

			 if(TempCA[2]>6){TempCA[3]=(TempCA[1]+10)/10;}else{ TempCA[3]=TempCA[1]/10;}
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
			case 'q':{	if(COUNTT<999){COUNTT+=1;}	}break;
			case 'a':{	if(COUNTT>1){COUNTT-=1;}	}break;
			default: COUNTT=COUNTT;
		}
	}
*/
    #pragma vector=TIMER1_A1_VECTOR
	__interrupt void Timer1a1_isr(void)
	{
		TA1CCTL1&=~CCIFG;

	   if(Tcountt==0){   P2OUT|=BIT2; }
		else{if(Tcountt>TCOUNTT) {  P2OUT&=~BIT2;} }
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

		    	if(min_t==1){side_t='R';G_IRA=1;}else{
		    	if(min_t==2){side_t='L';G_IRA=1;}else{
		    	if(min_t==3){side_t='L';G_IRA=1;}}}
		    	if(min_t==4){side_t='L';G_IRA=1;}

			 }else{sec_t+=1;}

       }else{count_t++;}

	}


