/*******************************************************************************
  Main Source File

  Company:
    Microchip Technology Inc.

  File Name:
    main.c

  Summary:
    This file contains the "main" function for a project.

  Description:
    This file contains the "main" function for a project.  The
    "main" function calls the "SYS_Initialize" function to initialize the state
    machines of all modules in the system
 *******************************************************************************/

// *****************************************************************************
// *****************************************************************************
// Section: Included Files
// *****************************************************************************
// *****************************************************************************

#include <stddef.h>                     // Defines NULL
#include <stdbool.h>                    // Defines true
#include <stdlib.h>                     // Defines EXIT_FAILURE
#include "definitions.h"                // SYS function prototypes


// *****************************************************************************
// *****************************************************************************
// Section: Main Entry Point
// *****************************************************************************
// *****************************************************************************


unsigned int spiReadWriteLoop(uint8_t *send, size_t sendLen, uint8_t *recv, size_t recLen){
   bool spiStatus = false;
   unsigned int count = 0;
   uint8_t sbuf;
   uint8_t rbuf;
    
    SS_Clear();
   // SYSTICK_DelayMs(10);
    while(count <= sendLen){
        sbuf = send[count];                         
        spiStatus = SERCOM0_SPI_WriteRead((void *)(&sbuf), 1U, (void *)(&rbuf), 1U);
        recv[count] = rbuf;
        SERCOM5_USART_Write(&recv, recLen);
        if(spiStatus) count++;
    }
        
    SYSTICK_DelayMs(1);
    SS_Set();
    return spiStatus;
}


//bool spiReadWriteBlock(void *send, size_t sendLen, void *recv, size_t recLen){
//    bool spiStatus = false;
//    SS_Clear();
//    SYSTICK_DelayMs(1);
//    spiStatus = SERCOM0_SPI_WriteRead(send, sendLen, recv, recLen);
//    SYSTICK_DelayMs(1);
//    SS_Set();
//    return spiStatus;
//}


void initSendbuf(uint8_t *buf){
//   uint8_t seed01 = '0';
    uint8_t seed02 = 'A';
//    for(unsigned int i = 0; i < 10; i++){
//        buf[i] = seed01+i;
//    }
    for(unsigned int j = 0; j < 26; j++){
//      buf[j+10] = seed02+j;
      buf[j] = seed02+j;
    }
}

int main ( void )
{
    /* Initialize all modules */
    SYS_Initialize ( NULL );
    uint8_t send[128];
    uint8_t recv[128];

    initSendbuf(send);
    size_t sendLen = 26U;
    size_t recLen = 26U;

    while ( true )
    {
        /* Maintain state machines of all polled MPLAB Harmony modules. */
        SYS_Tasks ( );
        spiReadWriteLoop(send, sendLen, recv, recLen);
        SYSTICK_DelayMs(10*1000);
//        spiReadWriteBlock((void *)send, sendLen - 10, (void *)recv, recLen);
//        SYSTICK_DelayMs(10*1000);
    }

    /* Execution should not come here during normal operation */

    return ( EXIT_FAILURE );
}


/*******************************************************************************
 End of File
*/

