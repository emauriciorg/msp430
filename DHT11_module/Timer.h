/*
 * Timer.h
 *
 *  Created on: 08/09/2016
 *      Author: Mauricio
 *
 *      this
 */

#ifndef TIMER_H_
#define TIMER_H_



	void delay_seconds(int tx)
	{

		 volatile int times,SerOK=0,countt=0;
			times=50*tx;

		 TACTL	 = ID_3|TASSEL_2|MC_1; //UP mode
			TACCR0	 = 40000; //each 0.02us
			TACCTL0 =OUTMOD_7;
			TACCR1=0;

			 do{

				while((TACCTL0&CCIFG)!=CCIFG);
					TACCTL0&=~CCIFG;

					if(countt<times){countt++;}
					else{
								 SerOK=10;
						}
			 }while(SerOK!=10); //number of times of the count
			 countt=0;
			TACCTL0|=TACLR;
			SerOK=0;
		}



	void delay_micros(int micro)
	{
		 volatile int times,SerOK=0,countt=0;
			//times=2*micro;


	 	   TACTL	 = ID_2|TASSEL_2|MC_1; //UP mode
		   TACCR0	 = 4; //each 1us
		   TACCTL0 =OUTMOD_7;
		   TACCR1=0;


		    do{

		    	while((TACCTL0&CCIFG)!=CCIFG);
				TACCTL0&=~CCIFG;

				if(countt<=micro){countt++;}
				else{
							 SerOK=10;
				    }
		    }while(SerOK!=10); //number of times of the count

			TACCTL0|=TACLR;

	}

	void delay_millis(int millis)
	{
		 volatile int times,SerOK=0,countt=0;
			times=500*millis;


	 	   TACTL	 = ID_3|TASSEL_2|MC_1; //UP mode
		   TACCR0	 = 4; //each 2us
		   TACCTL0 =OUTMOD_7;
		   TACCR1=0;


		    do{

		    	while((TACCTL0&CCIFG)!=CCIFG);
				TACCTL0&=~CCIFG;

				if(countt<times){countt++;}
				else{
							 SerOK=10;
				    }
		    }while(SerOK!=10); //number of times of the count
		    countt=0;
			TACCTL0|=TACLR;
			SerOK=0;

	}

	#endif /* TIMER_H_ */
