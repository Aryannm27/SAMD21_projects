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
int period = 1000;
int duty = 500;
int counter = 250;

int main ( void )
{
    /* Initialize all modules */
    SYS_Initialize ( NULL );
    TCC3_PWMStart( );
    TCC0_PWMStart( );
    TCC3_PWM24bitPeriodSet(period);
    TCC0_PWM24bitPeriodSet(period);
    TCC3_PWM24bitDutySet(TCC3_CHANNEL3,duty);
    TCC0_PWM24bitDutySet(TCC0_CHANNEL3,duty);
    TCC3_PWM24bitCounterSet(counter);
         
    while ( true )
    {
        /* Maiwhile ( true )maintain state machines of all polled MPLAB Harmony modules. */
        SYS_Tasks ( );
      
    }    
    /* Execution should not come here during normal operation*/
    return ( EXIT_FAILURE );
}


/*******************************************************************************
 End of File
*/

