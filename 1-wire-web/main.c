#include "msp430g2553.h"
#include"CDC.h"
#include"FBF.h"
#define OW_IN    P1IN
#define OW_OUT    P1OUT
#define    OW_DIR    P1DIR
#define    OW_PIN    BIT0

unsigned char scratchpad[10],i;

//------------------------------------------------------------------------------
// micro seconds delays
//
void usdelay(int interval){
                                // Setup TimerA
    TACCTL0 = CCIE;                // interrupt enabled
    TACCR0 = TAR + interval*8;  // micro secs @ 8Mhz Clock
    TA0CTL = TASSEL_2 + MC_2;      // SMCLK, continuous mode.
    LPM0;                        // suspend CPU
}

/*
 * This function generates the reset pulse and check for 1-wire device presence. If found, it retuns 1, else return 0
 */
int    owReset(void){
    int lineState;
    OW_OUT &= ~OW_PIN;            // Set P1.0 low
    OW_DIR |= OW_PIN;            // P1.0 output
    usdelay(480);                // H
    OW_DIR &= ~OW_PIN;            // Release the bus, it will float to high due to the pull-up resistor.
    usdelay(70);                // I
    lineState = OW_IN & OW_PIN;    // Sample input

    usdelay(300);                // slave TX presence pulse 60-240us
                                // This delay was missing, and without it, the further write and read were failing



    if (lineState == 1){
        return (1);
    } else {
        return (0);
    }
}

/*
 * READ_BIT - reads a bit from the one-wire bus.
 */

unsigned char owReadBit(void){
unsigned char lineState;
    OW_OUT &= ~OW_PIN;            // pull pin low to start timeslot
    OW_DIR |= OW_PIN;            // P1.0 output
    usdelay(6);                    // A=6us but we cannot make it that short.
                                // Change pin to input waiting for slave to put the data
    OW_DIR &= ~OW_PIN;            // Release the bus, the line will go high as it is pulled up to Vcc by a resistor
    usdelay(10);                // Wait E=9us
    lineState = OW_IN & OW_PIN;    // Sample input to read a bit
    usdelay(55);                // F=55us to complete the read slot
    return (lineState);
}

/*
 *    WRITE_BIT - writes a bit to the one-wire bus, passed in bitval.
 */
void owWriteBit(char bitval)
{
    OW_OUT &= ~OW_PIN;            // Set P1.0 low
    OW_DIR |= OW_PIN;            // P1.0 output

    usdelay(6);                    // A=6us but we cannot make it that short.
    if(bitval==1){
        OW_DIR &= ~OW_PIN;        // P1.0 input, release the bus
        usdelay(64);            // B
    } else {
        usdelay(50);            // C-A = 60-10=50
        OW_DIR &= ~OW_PIN;        // P1.0 input, release the bus
        usdelay(10);            // D
    }
}

/*
 *    READ_BYTE - reads a byte from the one-wire bus.
 */
unsigned char owReadByte(void){
unsigned char i;
unsigned char value = 0;
    for (i=0;i<8;i++) {
        if(owReadBit()){
            value|=0x01<<i; // reads byte in, one bit at a time and then shifts it left
        }
    }
    return(value);
}


/*
 * WRITE_BYTE - writes a byte to the one-wire bus.
 */
void owWriteByte(char val){
    unsigned char i;
    unsigned char temp;

    for (i=0; i<8; i++) {        // writes byte, one bit at a time
        temp = val>>i;            // shifts val right 'i' spaces
        temp &= 0x01;            // copy that bit to temp
        owWriteBit(temp);        // write bit in temp into
    }
}

void main(void)
{
    WDTCTL = WDTPW + WDTTMSEL;                  // WDT as interval timer,
                                                // f = SMCLK / 32768
                                                //Calibrate DCO for 8MHz operation
    BCSCTL1 = CALBC1_8MHZ;
    DCOCTL = CALDCO_8MHZ;
    inicio();
    __enable_interrupt();                        // Enable global interrupt

/*
 * Reset, Skip ROM, Convert T, Wait for 750us, Reset, Skip ROM, Read Scratchpad, Master loops a read slot to
 * receive data from the device LSB First
 */
    owReset();                // Check device presence
    owWriteByte(0xcc);        // Skip ROM
    owWriteByte(0x44);        // Convert Temperature
    usdelay(1000);
    owReset();                // Check device presence
    owWriteByte(0xcc);        // Skip ROM
    owWriteByte(0xbe);        // Read Scratchpad

    for (i=0; i<8; i++) {        // writes byte, one bit at a time
        scratchpad[i]= owReadByte();
        ec("working ");printuint( scratchpad[i]);borrar();
    }

    owReset();                // Stop reading

    LPM0;
}

// Timer A0 interrupt service routine. TIMERx_Ay_VECTOR.(x being the index of the timer, y of the vector for this timer)
#pragma vector=TIMER0_A0_VECTOR
__interrupt void Timer_A0 (void)
{
    TA0CTL = 0;                        // Stop Timer_A
    LPM0_EXIT;                        // Return active
}
