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

uint8_t rec ;
uint8_t send;
uint8_t dSend[30] = "abcdefghijklmnopqrstuvwxyz1234";

void callback(SERCOM_SPI_SLAVE_CALLBACK callBack,uintptr_t context)
{
           if( SERCOM0_SPI_ErrorGet() == SPI_SLAVE_ERROR_NONE )
            {
         for(int i=0;i<30;i++)
        {
        send = dSend[i];
        SERCOM0_SPI_Read(&rec ,sizeof(uint8_t));
        SERCOM5_USART_Write(&rec ,sizeof(uint8_t));
//        SYSTICK_DelayMs(55);
//        SERCOM0_SPI_Write(&send ,sizeof(uint8_t));
        }
           }
}

int main(void) {
    /* Initialize all modules */
    
    SYS_Initialize(NULL);
    SYSTICK_TimerStart();
    SYSTICK_TimerPeriodSet(10000);
    
    while (true) {
        
        /* Maintain state machines of all polled MPLAB Harmony modules. */
        SYS_Tasks();
   ///     SERCOM0_SPI_CallbackRegister( (void *)SERCOM0_SPI_InterruptHandler , 0 );
        SERCOM0_SPI_InterruptHandler(callback,0);
        
    }
    /* Execution should not come here during normal operation */
    
    return ( EXIT_FAILURE);
}


/*******************************************************************************
 End of File
 */
