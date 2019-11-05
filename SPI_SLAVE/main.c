#include <msp430G2553.h>
#include "nrf24l01p.h"
#include "CDC.h"
#include "FBF.h"

/*modificado 08/03/2017 by s314e
 * main.c
 */
void MainMenu(void);
void UartMenu(char);
void ReadConfReg(void);
void PrintReadReg(void);

int main(void)
{
  volatile unsigned int SpiData;
  SetClk();

  UartConf();

  InitNrf();//receiver mode
  EnableInterrupts();
  PrintMenu();
  while(1)
  {
    MainMenu();
	_delay_cycles(1000000);

  }
}

void PrintReadReg()
{
volatile char iprint=0;
	for(iprint=0;iprint<5;iprint++)
	{
		PrintUInt(DataRegR[iprint]);SingleSpace();
	}ClearTerminal();


}
void MainMenu()
{
	UartMenu(UartInput);
	UartInput=0;
}
void UartMenu(char UartOption)
{
	switch(UartOption)
	{
	case '1':SpiReadReg(R_RX_PAYLOAD,4);PrintReadReg(); break;//single TX
	case '2':ReadConfReg(); break;//read CONF
	case '3':PrintMenu(); break;//show sothing
	//case '4': P2OUT|=SpiCE;SpiSendCommand(REUSE_TX_PL);break;//continous Tx
	default:;//send not a command, list commands
	}

}
void ReadConfReg()
{
SpiReadReg((R_CONFIG),1);
PrintStr(" Status "); PrintUInt(nRfStatus);
PrintStr(" RegValue ");	PrintUInt(DataRegR[0]);ClearTerminal();
}
