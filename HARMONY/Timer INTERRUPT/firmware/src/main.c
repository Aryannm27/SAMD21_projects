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

void callback( TC_TIMER_STATUS status, uintptr_t context)
{
    LED_Clear();
    SYSTICK_DelayMs(3000);
    TC3_REGS->COUNT16.TC_INTFLAG |= TC_INTFLAG_OVF_Msk;
    
}

int main ( void )
{
     /* Initialize all modules */
    SYS_Initialize ( NULL );
    TC3_TimerStart( );
   // TC3_Timer16bitPeriodSet( 46875 );
    
    LED_Set();
    
    TC3_TimerCallbackRegister( callback , (uintptr_t) NULL );

    while ( true )
    {
        /* Maintain state machines of all polled MPLAB Harmony modules. */
        SYS_Tasks( );
    
    }
    /* Execution should not come here during normal operation */

    return ( EXIT_FAILURE );
}


/*******************************************************************************
 End of File
*/

