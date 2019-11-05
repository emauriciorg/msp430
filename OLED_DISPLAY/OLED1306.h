/*
 * OLED1306.h
 *
 *  Created on: 31/03/2016
 *      Author: Mauricio
 */
#include"GYRO.h"
#ifndef OLED1306_H_
#define OLED1306_H_

#define SLCSAFPAM 0X00 //0X0F set lower column start address for page addressing Mode
#define SHCSAFPAM 0X10 //0X1FSet Higher Column Start Address for Page Addressing Mode (10h~1Fh)
#define SDCDR     0X1F //0X1F set display divide clock ratio
#define SMAM      0X20 //Set Memory Addressing Mode
#define SCA       0X21 //Set Column Address (21h)
#define SPA       0X22//Set Page Address (22h)
#define SDSL      0X40//7FH Set Display Start Line (40h~7Fh)
#define SCCFB     0X81//Set Contrast Control for BANK0 (81h)
#define SSR       0XA0//Set Segment Re-map (A0h/A1h)
#define EDO       0xA4//Entire Display ON   (A4h/A5h)
#define SNID      0xA6//Set Normal/Inverse Display (A6h/A7h)
#define SMR       0XA8//Set Multiplex Ratio (A8h)
#define SDOOF     0XAE//0XAF Set Display ON/OFF (AEh/AFh)
#define SPSAFPAM  0XB0//0XB7 Set Page Start Address for Page Addressing Mode (B0h~B7h)
#define SCOSD     0XC0//0XC8 Set COM Output Scan Direction (C0h/C8h)
#define SDO       0XD3//Set Display Offset (D3h)
#define SDCDROF   0XD5//Set Display Clock Divide Ratio/ Oscillator Frequency (D5h)
#define SPCP      0XD9//Set Pre-charge Period (D9h)
#define SCPHC     0XDA//Set COM Pins Hardware Configuration (DAh)
#define SVCDL     0XDB//Set VCOMH  Deselect Level (DBh)
#define NOPNOP    0XE3//NON OPERATION COMMANDNOP (E3h)
#define HZSS      0X26//Horizontal Scroll Setup (26h/27h)
#define CVAHSS    0X29//Continuous Vertical and Horizontal Scroll Setup (29h/2Ah)
#define DeaSc     0x2E//Deactivate Scroll (2Eh)
#define ActSc     0x2F//Activate Scroll (2Fh)
#define SVSA      0xA3//Set Vertical Scroll Area(A3h)



		void init_oled()
		{

			gw(0xAE,0XAE); //set display off
			gw(0xD5,0x80);//clock divider
			gw(0xA8, 0x3f); //multiplex ratio
			gw(0xD3, 0x00); //default
			gw(0x40,0x40);//set start line
			gw(0x8d,  0x10);// set charge pump
			gw(0xA1,0xA1);// remap segment
			gw(0xc8,0xc8);//scan direction
			gw(0xDA, 0x12);//pin config
			gw(0x81, 0x9f); //contrast
			gw(0xD9, 0x22); //precharge period
			gw(0xDB, 0x40); //desselect level
			gw(0xA4,0x40); //set entire display on/off
			gw(0xA6,0xA6); //normal inverse display
			//clear screen//
			gw(0xaf,0xaf);//set on display


		}







#endif /* OLED1306_H_ */
