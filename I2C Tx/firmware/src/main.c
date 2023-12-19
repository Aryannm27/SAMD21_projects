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
#include "Interrupts.h"

// *****************************************************************************
// *****************************************************************************
// Section: Main Entry Point
// *****************************************************************************
// *****************************************************************************
 

//************************************************************
// *****************************************************************************
// Section: Main Entry Point
// *****************************************************************************
// *****************************************************************************
uint8_t data[] = "Hello";

int main ( void )
{
    /* Initialize all modules */
    SYS_Initialize ( NULL );
    SYSTICK_TimerInitialize ();
    SYSTICK_TimerPeriodSet(10000);
    SYSTICK_TimerStart();    


    while ( true )
    {
        /* Maintain state machines of all polled MPLAB Harmony modules. */
        
         SYS_Tasks ( );
      
         for(int i=0;i<sizeof(data);i++)
         {
            SERCOM2_I2C_Write(0x40 , &data[i] , sizeof(data) );
            //SYSTICK_DelayMs(100);
         }
        
         
    //    SERCOM2_I2C_Write(0x51, &data, sizeof(data));
    //    SYSTICK_DelayMs(500);
         
    }

    /* Execution should not come here during normal operation */

    return ( EXIT_FAILURE );
}



/*******************************************************************************
 End of File
*/

