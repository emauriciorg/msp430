/*
 * Timer.h
 *
 *  Created on: 29/12/2016
 *      Author: Mauricio
 */

#ifndef TIMER_H_
#define TIMER_H_

void Timer1En();
void EnTimer();
void Timer1En()
{
//TA1CCR0=3999;
TA1CCR0=3999;
TA1CCTL1=OUTMOD_7; //no capture mode+CCIA+Asynchronous en capture mode+modo comparacion+
TA1CTL=TASSEL_2|ID_3|MC_1|TAIE;
}

void EnTimer()
{
  TA1CTL	 = ID_2|TASSEL_2|MC_1;
  TA1CCR0	 = 40;
  TA1CCTL1 =OUTMOD_7| CCIE;
  TA1CCR1=000;
}


#endif /* TIMER_H_ */
