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

//uint8_t data[26] = "abcdefghijklmnopqrstuvwxyz";
uint8_t rec[27];
uint8_t send[] = "abcdefghijklmnopqrstuvwxyz";


void APP_Callback(DMAC_TRANSFER_EVENT status, uintptr_t context)
{
    if(status == DMAC_TRANSFER_EVENT_COMPLETE)
    {       
         DMAC_ChannelTransfer (DMAC_CHANNEL_0 ,(const void *)&SERCOM1_REGS->SPIM.SERCOM_DATA, &rec , sizeof(rec)); 
         SERCOM5_USART_Write(rec,sizeof(rec));
         
    }
}


int main ( void )
{
    /* Initialize all modules */
    SYS_Initialize ( NULL );
    SYSTICK_TimerStart();
    SYSTICK_TimerPeriodSet(10000);
    DMAC_ChannelCallbackRegister(DMAC_CHANNEL_0, APP_Callback, 0);
 
    
    while ( true )
    {
        SYS_Tasks ( );
        /* Maintain state machines of all polled MPLAB Harmony modules. */
      //  DMAC_ChannelTransfer (DMAC_CHANNEL_0 ,(const void *)&SERCOM1_REGS->SPIM.SERCOM_DATA, &rec , sizeof(rec));  
//        SERCOM5_USART_Write(rec,sizeof(rec));
       // SYSTICK_DelayMs(100);
        
         DMAC_ChannelTransfer (DMAC_CHANNEL_1 , &send  ,(const void *)&SERCOM1_REGS->SPIS.SERCOM_DATA, sizeof(send));
       // SYSTICK_DelayMs(100);
    }

    /* Execution should not come here during normal operation */

    return ( EXIT_FAILURE );
}


/*******************************************************************************
 End of File
*/

