/*
 * File:   timing.c
 * Author: Mike Peters
 *
 * 1000750876
 */

#include <timer.h>
#include "../include/main.h"


void _delay_HalfSec(void)
{
    int i, j = 0;
    for (i = 0; i < 800; i++)
    {
        for (j=0; j < 2550; j++)
        {
        }
     }
    return;
}

void _delay_Seconds(int seconds)
{
    int i, j, time = 0;
    for (time = 0; time < seconds; time++)
    {
        for (i = 0; i < (1600); i++)
        {
            for (j=0; j<(4000); j++)
            {
            }
        }
    }
   return;
}

void SetupTimer1(void)
{
    OpenTimer1(
        T1_ON           &
        T1_IDLE_CON     &
        T1_GATE_OFF     &
        T1_PS_1_256       &
        T1_SOURCE_INT,
        0xFFFF
    );
    ConfigIntTimer1(
           T1_INT_PRIOR_0   &
           T1_INT_OFF
    );
    return;
}

void SetupTimer2(void)
{
    OpenTimer2(
        T2_ON               &
        T2_IDLE_CON         &
        T2_GATE_OFF         &
        T2_PS_1_256         &
        T2_32BIT_MODE_OFF   &
        T2_SOURCE_INT,

        0x3d08
    );
    ConfigIntTimer2(
           T2_INT_PRIOR_1   &
           T2_INT_ON
    );

    return;
}
