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


uint8_t rec;

bool callback(SERCOM_I2C_SLAVE_TRANSFER_EVENT SERCOM_I2C_SLAVE_TRANSFER_EVENT_ERROR, uintptr_t contextHandle)
{
    bool x;
    if (SERCOM2_I2C_ErrorGet() != SERCOM_I2C_SLAVE_ERROR_ALL)
    {
      x=true;  
    }
    else
    {
      x=false;
    }
    return x;
}

int main ( void )
{
    /* Initialize all modules */
    SYS_Initialize ( NULL );
    SYSTICK_TimerInitialize ();
    SYSTICK_TimerPeriodSet (10000);
    SYSTICK_TimerStart();
    SERCOM2_I2C_CallbackRegister(callback,0);

    while ( true )
    {
        /* Maintain state machines of all polled MPLAB Harmony modules. */
        SYS_Tasks();
        rec = SERCOM2_I2C_ReadByte();
    //    DMAC_ChannelTransfer (DMAC_CHANNEL_0,(const void *)&SERCOM2_REGS->I2CM.SERCOM_DATA , &rec , sizeof(rec));
        SERCOM5_USART_Write(&rec,sizeof(rec));
    //    SYSTICK_DelayMs(100);
        
    }

    /* Execution should not come here during normal operation */

    return ( EXIT_FAILURE );
}

/*******************************************************************************
 End of File
*/

