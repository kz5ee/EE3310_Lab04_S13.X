/* 
 * File:   config.h
 * Author: mike
 *
 * Created on November 3, 2012, 11:44 PM
 */

#ifndef CONFIG_H
#define	CONFIG_H

#ifdef	__cplusplus
extern "C" {
#endif
#include <uart.h>
#include <pps.h>

extern void UART1_Config(void);

//Baud rate and UARTUBRG setting for UART 1
#define __FOSC_ 8000000
#define __FTCY_ (__FOSC_/2)
#define __BAUD_ 9600L //<--- Desired Baud rate CHANGE THIS
#define __BAUDUART1_ ((__FTCY_/(16*__BAUD_))-1)
//End of Baud Rate


#ifdef	__cplusplus
}
#endif

#endif	/* CONFIG_H */

