#ifndef L3GD20_H_
#define L3GD20_H_


#define WHO_AM_I            0X0F         //R
#define CTRL_REG1          	0X20         //RW
#define CTRL_REG2          	0X21         //RW
#define CTRL_REG3          	0X22         //RW
#define CTRL_REG4          	0X23         //RW
#define CTRL_REG5          	0X24         //RW
#define REFERENCE	       		0X25         //RW
#define OUT_TEMP           	0X26        //R
#define STATUS_REG         	0X27        //R
#define OUT_X_L            		0X28        //R
#define OUT_X_H           		0X29       	//R
#define OUT_Y_L            		0X2A       //R
#define OUT_Y_H            	0X2B        //R
#define OUT_Z_L            		0X2C       //R
#define OUT_Z_H            	0X2D       //R
#define  FIFO_CTRL_REG    0X2E        //RW
#define  FIFO_SCR_REG      0X2F        //R
#define  INT1_CFG          		0x30        //RW
#define  INT1_SRC          		0x31       //R
#define INT1_TSH_XH        0x32        //RW
#define INT1_TSH_XL        	0x33        //RW
#define INT1_TSH_YH        0x34        //RW
#define INT1_TSH_YL        	0x35        //RW
#define INT1_TSH_ZH        0x36        //RW
#define INT1_TSH_ZL        	0x37        //RW
#define INT1_DURATION  	0x38       //RW

#define SADLR   0xD5	//SLAVEADRESSLOW     READ
#define SADLW	0XD4	//SLAVEADRESSLOW     WRITE
#define SADHR	0XD7	//SLAVEADRESSHIGH    READ
#define SADHW 	0XD6	//SLAVEADRESSHIGH    WRITE








#endif
