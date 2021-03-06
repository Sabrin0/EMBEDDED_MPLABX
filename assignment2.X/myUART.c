/*
 * File:   myUART.c
 * Author: francesco testa
 *
 * Created on 18 dicembre 2020, 18.41
 */

#include <string.h>
#include <stdio.h>
#include "myUART.h"
#include "global_&_define.h"
#include "myBuffer.h"


void UART_config(int port) {
    switch (port){
        case 1:
            U2BRG = 11; //    (1843200)/(16*(9600))  set the bound rate (9600) of transmission
            U2MODEbits.UARTEN = 1; //enable UART module 
            U2STAbits.UTXEN = 1; // enable transmission 
            break;
        case 2:
            U1BRG = 11; //    (1843200)/(16*(9600))  set the bound rate (9600) of transmission
            U1MODEbits.UARTEN = 1; //enable UART module 
            U1STAbits.UTXEN = 1; // enable transmission 
            break;         
    }
    
}

// sand a string through UART2
void send_string_UART2(char* msg){

    int i; 
    for (i = 0; i < strlen(msg) +1; i++){
    U2TXREG = msg[i];
    }
        
}

// Put a char in the UART buffer every time there is a new interrupt msg from UART
void __attribute__((__interrupt__, __auto_psv__)) _U2RXInterrupt () {
    IFS1bits.U2RXIF = 0;                            // Reset rx interrupt flag
    int val = U2RXREG;                              // Read from rx register
    writeBuf(&UARTbuf, val);    // Save value in buffer
}