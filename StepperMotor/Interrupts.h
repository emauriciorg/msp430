/*
 * Interrupts.h
 *
 *  Created on: 24/01/2017
 *      Author: Mauricio
 */

#ifndef INTERRUPTS_H_
#define INTERRUPTS_H_

/*
#pragma vector=USCIAB0RX_VECTOR
__interrupt void RXserial_isr(void)
{
	IFG2&=~UCA0RXIFG;
	DES=UCA0RXBUF;
	switch(DES)
	{
		case 'q':{	if(an1<995){an1+=1;}	}break;
		case 'a':{	if(an1>4){an1-=1;}	}break;

		case 'w':{	if(an2<995){an2+=1;}	}break;
		case 's':{	if(an2>4){an2-=1;}	}break;

		case '1':{TA1CCR1+=1;	}break;
		case '2':{TA1CCR1-=1;	}break;
		case 'e':{TA1CCR1+=50;	}break;
		case 'd':{TA1CCR1-=50;	}break;

	}
}
*/
#endif /* INTERRUPTS_H_ */
