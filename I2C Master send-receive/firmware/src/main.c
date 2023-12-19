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

uint8_t data1[] = "1234567890" ;
uint8_t rec[15];

// *****************************************************************************
// *****************************************************************************
// Section: Main Entry Point
// ***************************************H**************************************
// *****************************************************************************

int main ( void )
{
    /* Initialize all modules */
    
    SYS_Initialize ( NULL );
    SYSTICK_TimerInitialize ();
    SYSTICK_TimerPeriodSet (10000);
    SYSTICK_TimerStart();
    
    while ( true )
    {
        /* Maintain state machines of all polled MPLAB Harmony modules. */
        
         SYS_Tasks ( );
//         for(int i=0;i<6;i++)
//         {
//            SERCOM2_I2C_Write(40 , &data[i], sizeof(data));
//            SYSTICK_DelayMs(1000);
//         }
         
//         for(int i=0;i<sizeof(data1);i++)
//         {
         SERCOM1_I2C_Write( 0x40 , data1 , sizeof(data1));

        
    }

    /* Execution should not come here during normal operation */

    return ( EXIT_FAILURE );
}



/*******************************************************************************
 End of File
*/

