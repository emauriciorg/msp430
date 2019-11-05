/*
 * StepMotor.h
 *
 *  Created on: 24/01/2017
 *      Author: Mauricio
 */

#ifndef STEPMOTOR_H_
#define STEPMOTOR_H_


#define CoilA1  BIT0
#define CoilA2	BIT1
#define CoilB1	BIT2
#define CoilB2	BIT3
#define CoilAB CoilA1|CoilA2|CoilB1|CoilB2


/*
 * 1->
 * 3->
 * 2->nothing
 * 0->nothing
 *
 *
 * w<-
 * e<-
 * */

const char CoilASeq[4]={0x00,0x01,0x02,0x03};
const char CoilBSeq[4]={0x00,0x04,0x08,0x0C};


void InitStepperMotor(void);
void SendStepperMotor(char, char);
void InitStepperMotor(void)
{
	P2SEL&=~(CoilA1|CoilA2| CoilB1|	 CoilB2);
	P2DIR|= (CoilA1|CoilA2| CoilB1|	 CoilB2);
	P2SEL2&=~(CoilA1|CoilA2| CoilB1|CoilB2);
	P2OUT&=~(CoilA1|CoilA2| CoilB1|	 CoilB2);


}
void rotate(void)
{
//	SendStepperMotor(0,0);
	SendStepperMotor(1,0);
	SendStepperMotor(0,4);
	SendStepperMotor(2,0);
	SendStepperMotor(0,3);
}
void SendStepperMotor(char Coil1, char Coil2)
{
__delay_cycles(4000000);
	P2OUT&=~CoilAB;
	P2OUT=CoilASeq[Coil1]|CoilBSeq[Coil2];

}


#endif /* STEPMOTOR_H_ */
