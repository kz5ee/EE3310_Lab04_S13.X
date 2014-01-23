/*
 * File:   traffic_light.c
 * Author: Mike Peters
 *
 * 1000750876
 */

#include "../include/main.h"

UINT ChangeDirection  = 0;

/* This code can be done inside of the light functions.
void ChangeLights(void)
{
    if((LIGHT_STATE == GREEN_ARROW) && (DIRECTION == EW))
    {
        EWRed(OFF);
        EWGreenArrow(ON);
    }
    else if ((LIGHT_STATE == GREEN_ARROW) && (DIRECTION == NS))
    {
        NSRed(OFF);
        NSGreenArrow(ON);
    }

    if((LIGHT_STATE == GREEN) && (DIRECTION == EW))
    {
        EWGreenArrow(OFF);
        EWGreen(ON);
    }
    else if ((LIGHT_STATE == GREEN) && (DIRECTION == NS))
    {
        NSGreenArrow(OFF);
        NSGreen(ON);
    }

    if((LIGHT_STATE == YELLOW) && (DIRECTION == EW))
    {
        EWGreen(OFF);
        EWYellow(ON);
    }
    else if ((LIGHT_STATE == YELLOW) && (DIRECTION == NS))
    {
        NSGreen(OFF);
        NSYellow(ON);
    }
    return;
}*/
void Green_Arrow(void)
{
    int TimerVal = ReadTimer1();
    if(TimerVal != 3)
    { return; }
    else
    {
        ChangeDirection = 0;
//    if (ChangeDirection !=0)
//    {
//      _delay_Seconds(1);
//      _delay_HalfSec();
//      ChangeDirection = 0;
//    }
//    else
//    {

        if (DIRECTION == NS)
        {
            NSRed(OFF);
            EWRed(ON);
            NSGreenArrow(ON);
        }
        else
        {
            EWRed(OFF);
            NSRed(ON);
            EWGreenArrow(ON);
        }

        TMR1 = 0;
        LIGHT_STATE = GREEN;    
    }

#ifdef DEBUG_CODE
     printf("Light Changing to Green Arrow.\n");
#endif
    

//    _delay_Seconds(8);
//    LIGHT_STATE = GREEN;

    return;
}

void Green(void)
{
    if (TMR1 != 16)
    { return; }
    else
    {
        if (DIRECTION == NS)
        {
            NSGreenArrow(OFF);
            NSGreen(ON);
        }
        else
        {
            EWGreenArrow(OFF);
            EWGreen(ON);
        }

        WriteTimer1(0);
        LIGHT_STATE = YELLOW;
    }
#ifdef DEBUG_CODE
     printf("Light Changing to Green.\n");
#endif


//     _delay_Seconds(22);
//    LIGHT_STATE = YELLOW;
    return;
}

void Yellow(void)
{
    if (ReadTimer1() != 44)
    { return; }
    else
    {
        if (DIRECTION == NS)
        {
            NSGreen(OFF);
            NSYellow(ON);
        }
        else
        {
            EWGreen(OFF);
            EWYellow(ON);
        }

        WriteTimer1(0);
        LIGHT_STATE = RED;
    }
#ifdef DEBUG_CODE
     printf("Light Changing to Yellow.\n");
#endif
    //ChangeLights();

#ifndef __TIMER_DELAY__
     _delay_Seconds(5);
    LIGHT_STATE = RED;
#endif
    return;
}

void Red(void)
{
#ifdef DEBUG_CODE
     printf("Light Changing to Red.\n");
#endif
    if(DIRECTION == NS)
    { NSYellow(OFF); }
    else
    { EWYellow(OFF); }

    ChangeDirection = 1;

    LIGHT_STATE = GREEN_ARROW;
    
    if(DIRECTION == NS)
    { NSRed(ON); }
    else
    { EWRed(ON); }
    return;
}

void Traffic_Light_GO(void)
{
    
#ifndef __TIMER_DELAY__
    switch (LIGHT_STATE)
    {
        case(GREEN_ARROW):
            Green_Arrow();
            break;

        case(GREEN):
            Green();
            break;

        case(YELLOW):
            Yellow();
            break;
            
        case(RED):
            Red();
            break;

    }
#endif
#ifdef DEBUG_CODE
    printf("Timer2 = %u (0x%04X)\n", TMR2, TMR2);
#endif
    if (ChangeDirection == 0 && LIGHT_STATE == GREEN_ARROW)
    {
        TMR1 = 3;
        WriteTimer1(3);
        Green_Arrow();
    }
    if((ChangeDirection == 1) && (DIRECTION == EW))
    {
        DIRECTION = NS;
#ifdef DEBUG_CODE
     printf("Direction Changed to N/S\n");   
#endif
    }
    else if((ChangeDirection == 1) && (DIRECTION == NS))
    {
        DIRECTION = EW;
#ifdef DEBUG_CODE
     printf("Direction Changed to E/W\n");   
#endif
    }
    return;
}

void __attribute__((interrupt,auto_psv))_ISR _T2Interrupt(void)
{
    T2CONbits.TON = OFF;
    
    if(LIGHT_STATE == GREEN_ARROW)
    { Green_Arrow();}

    if(LIGHT_STATE == GREEN)
    { Green();}

    if(LIGHT_STATE == YELLOW)
    { Yellow();}

    if(LIGHT_STATE == RED)
    { Red();}
    

    _T2IF = 0; //Clear Timer2 interrupt flag
    T2CONbits.TON = ON;
    return;
}