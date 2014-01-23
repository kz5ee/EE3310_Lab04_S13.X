/*
 * File:   main.c
 * Author: Mike Peters
 *
 * 1000750876
 */

#include <stdio.h>
#include <stdlib.h>
#include <p24Hxxxx.h>
#include <peripheralversion.h>
#include <Generic.h>

#include "./include/main.h"
/*
 WORDS OF POWER

 * The configuration below sets up the chip configuration.
 * FBS:         Write to Boot Segment, No boot program to flash, No Boot RAM
 * FGS:         Program Memory not write protected, Code protect disabled
 * FOSCSEL:     Use Internal Fast RC, Device startup with selected oscillator source
 * FOSC:        OSC2 pin is digital I/O, No Primary Oscillator, Clock Switching Enabled
 *                Fail-Safe Clock Monitor disabled
 * FWDT:        Postscalar 1:8192, Prescalar 1:32, WDT is in Non-Window mode, WDT enabled by software
 * FPOR:        POR set for 128ms
 * FICD:        Use PGD1 for programming, JTAG Disabled
 */
_FBS(BWRP_WRPROTECT_OFF & BSS_NO_BOOT_CODE )
_FGS(GWRP_OFF & GCP_OFF)
_FOSCSEL( FNOSC_FRCPLL & IESO_OFF)//Will need to change to External OSCillator
_FOSC(OSCIOFNC_ON & POSCMD_NONE & FCKSM_CSECMD)
_FWDT( WDTPOST_PS8192 & WDTPRE_PR32 & WINDIS_OFF & FWDTEN_OFF)
_FPOR( FPWRT_PWR128)
_FICD( ICS_PGD1 & JTAGEN_OFF)

/*
 * 
 */

_Direction DIRECTION;
_Light_State LIGHT_STATE;

int main(int argc, char** argv) {
    //OSCTUN = 0b10111;

    void Ludacris_Speed_GO(void);
    //Ludacris_Speed_GO();

    AD1PCFGL = 0xffff;

    TRISBbits.TRISB15 = OUT;
    TRISBbits.TRISB14 = OUT;
    TRISBbits.TRISB13 = OUT;
    TRISBbits.TRISB12 = OUT;

    TRISBbits.TRISB11 = OUT;
    TRISBbits.TRISB10 = OUT;
    TRISBbits.TRISB9 = OUT;
    TRISBbits.TRISB8 = OUT;

    TRISB = OUT;
    DIRECTION = NS;
    LIGHT_STATE = GREEN_ARROW;
 
#ifdef DEBUG_CODE
#include "../EE3310_Lab04.X/include/config.h"
   UART1_Config();
   LightsTest();
   //printf("Oscillator = 0x%X", );
   printf("Initial Direction is N/S.\n");
   printf("Ready to go!!\n\n");
#endif
   T2CONbits.TON = ON;
    while(1)
    {
        Traffic_Light_GO();
        //_delay_HalfSec();
        //LATBbits.LATB15 = !LATBbits.LATB15;
        
    }
    return (EXIT_SUCCESS);
}

inline void Ludacris_Speed_GO()
{
    //This code from Microchip Family Ref. 39 Oscillator(Part III)
    //Example 39-1
    //Configure PLL prescaler, PLL postscaler, PLL divisor
    PLLFBD = 41; // M = 43
    CLKDIVbits.PLLPOST = 0; // N2 = 2
    CLKDIVbits.PLLPRE = 0; // N1 = 2
    // Initiate Clock Switch to Internal FRC with PLL (NOSC = 0b001)
    __builtin_write_OSCCONH(0x01);
    __builtin_write_OSCCONL(0x01);
    // Wait for Clock switch to occur
    while (OSCCONbits.COSC != 0b001);
    // Wait for PLL to lock
    while(OSCCONbits.LOCK != 1) {};
    return;
}

inline void LightsTest(void)
{
    printf("Testing Lights\n");
    NSGreenArrow(ON);
    _delay_HalfSec();
    NSGreen(ON);
    _delay_HalfSec();
    NSYellow(ON);
    _delay_HalfSec();
    NSRed(ON);
    _delay_HalfSec();

    EWGreenArrow(ON);
    _delay_HalfSec();
    EWGreen(ON);
    _delay_HalfSec();
    EWYellow(ON);
    _delay_HalfSec();
    EWRed(ON);
    _delay_HalfSec();

    NSGreenArrow(OFF);
    _delay_HalfSec();
    NSGreen(OFF);
    _delay_HalfSec();
    NSYellow(OFF);
    _delay_HalfSec();
    NSRed(OFF);
    _delay_HalfSec();

    EWGreenArrow(OFF);
    _delay_HalfSec();
    EWGreen(OFF);
    _delay_HalfSec();
    EWYellow(OFF);
    _delay_HalfSec();
    EWRed(OFF);
    printf("Testing Lights Completed\n");
    return;
}
