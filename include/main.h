/* 
 * File:   main.h
 * Author: Mike Peters
 * 1000750876
 *
 * Created on February 11, 2013, 4:17 AM
 */

#ifndef MAIN_H
#define	MAIN_H

#include <stdio.h>
#include <p24Hxxxx.h>
#include <peripheralversion.h>
#include <Generic.h>
#include <timer.h>

#ifdef	__cplusplus
extern "C" {
#endif

#define DEBUG_CODE
#define __TIMER_DELAY__

#define ON                              1
#define OFF                             0

#define IN                              1
#define OUT                             0

#define NSGreenArrow(state)             (LATBbits.LATB15 = (state))
#define NSGreen(state)                  (LATBbits.LATB14 = (state))
#define NSYellow(state)                 (LATBbits.LATB13 = (state))
#define NSRed(state)                    (LATBbits.LATB12 = (state))
#define EWGreenArrow(state)             (LATBbits.LATB11 = (state))
#define EWGreen(state)                  (LATBbits.LATB10 = (state))
#define EWYellow(state)                 (LATBbits.LATB9  = (state))
#define EWRed(state)                    (LATBbits.LATB8  = (state))

typedef enum{
    NS,
    EW
}_Direction;
extern _Direction DIRECTION;

typedef enum{
    GREEN_ARROW,
            GREEN,
            YELLOW,
            RED
}_Light_State;
extern _Light_State LIGHT_STATE;

void LightsTest(void);
void _delay_ms(int);
void _delay_HalfSec(void);
void _delay_Seconds(int);
void Traffic_Light_GO(void);

void SetupTimer1(void);
void SetupTimer2(void);



#ifdef	__cplusplus
}
#endif

#endif	/* MAIN_H */

