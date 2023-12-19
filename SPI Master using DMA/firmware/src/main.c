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

uint8_t data[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
uint8_t rec[35];

//void sendSPIMaster(uint8_t *data, size_t dataLen){
//    
//    DMAC_ChannelTransfer (DMAC_CHANNEL , data , SERCOM0_REGS , dataLen);
//    //return the proper value
//}


int main ( void )
{
    /* Initialize all modules */
    SYS_Initialize ( NULL );
    SYSTICK_TimerStart();
    SYSTICK_TimerPeriodSet(10000);

    
    
    while (true) {
        /* Maintain state machines of all polled MPLAB Harmony modules. */
        SYS_Tasks();
 //       sendSPIMaster(&data,dataLen);
        DMAC_ChannelTransfer (DMAC_CHANNEL_0 , &data , (const void *)&SERCOM1_REGS->SPIM.SERCOM_DATA , sizeof(data)); 
        //SYSTICK_DelayMs(100);
        
        DMAC_ChannelTransfer (DMAC_CHANNEL_1 ,(const void *)&SERCOM1_REGS->SPIS.SERCOM_DATA , &rec , sizeof(rec));
        SERCOM5_USART_Write(rec,sizeof(rec));
        
    }

    /* Execution should not come here during normal operation */

    return ( EXIT_FAILURE );
}


/*******************************************************************************
 End of File
*/

