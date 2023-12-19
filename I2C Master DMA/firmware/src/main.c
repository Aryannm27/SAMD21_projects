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
bool z =true;
uint8_t data =  'K' ;
uint8_t send[] = "HELLO Master";

int main ( void )
{
    /* Initialize all modules */
    SYS_Initialize ( NULL );
    SYSTICK_TimerInitialize ();
    SYSTICK_TimerPeriodSet (10000);

    while ( true )
    {
        /* Maintain state machines of all polled MPLAB Harmony modules. */
        SYS_Tasks ( );
        
       // SERCOM1_I2C_Write( 0x35 ,&data, sizeof(data));
        //SERCOM1_I2C_SendAddress( 0x35 , z);
        SERCOM1_REGS->I2CM.SERCOM_ADDR =  0x35 ;
        DMAC_ChannelTransfer(DMAC_CHANNEL_0,(const void *) &send , (const void *)&SERCOM1_REGS->I2CM.SERCOM_DATA , sizeof(send));
       //  SYSTICK_DelayMs(10);
        
    }

    /* Execution should not come here during normal operation */

    return ( EXIT_FAILURE );
}




/*******************************************************************************
 End of File
*/

