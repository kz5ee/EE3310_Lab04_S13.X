/*
 * File:   UART_Setup.c
 * Author: Mike Peters
 *
 * Created on October 28, 2012, 6:27 PM
 */

#include <uart.h>
#include "../include/config.h"

/*
 * Uncomment InvertBits to invert the bits to Active High
 */
//#define InvertRxTxBits
#define TRIS_U1TX       (TRISBbits.TRISB6 = 0)
#define TRIS_U1RX       (TRISBbits.TRISB7 = 1)
#define MAP_U1TX        (PPSOutput(OUT_FN_PPS_U1TX, OUT_PIN_PPS_RP6))
#define MAP_U1RX        (PPSInput(PPS_U1RX, PPS_RP7))

//Set up UART and pins
//UART Pins are on RPn (remappable)

void UART1_Config(void){

    OpenUART1((
            UART_EN &                   //Enable UART Module
            UART_IDLE_CON &             //Work while idle
            UART_IrDA_DISABLE &         //Disable Infared decoder
            UART_MODE_SIMPLEX &         //UART Simplex mode (RTS pin)
            UART_UEN_00 &               //TX/RX pins configured all other latched
            UART_DIS_WAKE &             //Disable wake on Start bit
            UART_DIS_LOOPBACK &         //Disable loopback
            UART_DIS_ABAUD &            //Disable Auto Baud
            UART_UXRX_IDLE_ONE &        //Receive idle is 1
            UART_BRGH_SIXTEEN &         //16 clocks per bit period
            UART_NO_PAR_8BIT &          //No parity bit
            UART_1STOPBIT               //One stop bit
            ),
            (
            UART_INT_TX_LAST_CH &       //
            UART_IrDA_POL_INV_ZERO &    //
            UART_SYNC_BREAK_DISABLED &  //
            UART_TX_ENABLE &            //
            UART_TX_BUF_NOT_FUL &       //
            UART_INT_RX_CHAR &          //
            UART_ADR_DETECT_DIS &       //
            UART_RX_OVERRUN_CLEAR       //
            ),
            (
            __BAUDUART1_ //Baud rate
            ));
    ConfigIntUART1(
                UART_RX_INT_DIS &
                UART_RX_INT_PR1 &
                UART_TX_INT_DIS &
                UART_TX_INT_PR1
            );
    

#ifdef InvertRxTxBits
    U1STAbits.UTXINV = 0;
    U1MODEbits.URXINV = 0;
#endif

    //Set the tristate and map pins for Uart
    TRIS_U1TX;
    TRIS_U1RX;
    MAP_U1TX;
    MAP_U1RX;

    

}

