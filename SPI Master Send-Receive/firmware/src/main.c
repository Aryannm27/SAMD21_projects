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
// ****************************************************************************

int data[128] ;
int rec[128];
int rx[128] ;

int main(void) {
    /* Initialize all modules */

    SYS_Initialize(NULL);
    SYSTICK_TimerStart();
    SYSTICK_TimerPeriodSet(10000);
    
    for(int i=0;i<=127;i++)
    {
        data[i]=i;
    }

      for(int i=127;i>=0;i++)
    {
        rx[i]=i;
    }

    while (true) {
        /* Maintain state machines of all polled MPLAB Harmony modules. */
        SYS_Tasks();

        SS_Clear();
        for (int i = 0; i<= sizeof(rx);i++) {
            SERCOM1_SPI_WriteRead(&data[i], sizeof (data), &rec[i], sizeof (rec));
            SERCOM5_USART_Write( &rec[i], sizeof(rec));
        }
        SS_Set();
        
        if(rx==rec)
        {
            LED_Clear(); 
        }
        else
        {
            LED_Set();
        }
    }

    /* Execution should not come here during normal operation */
    return ( EXIT_FAILURE);
}


/*******************************************************************************
 End of File
 */

