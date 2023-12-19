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
uint8_t data[26]; 
uint8_t data1[] = "abcdefghijklmnopqrstuvwxyz";
 
// void callBack(  )
//{
//     if(SERCOM1_SPI_ErrorGet() == SPI_SLAVE_ERROR_NONE)
//     {
//        for(int i=0;i<=sizeof(data);i++){
//            SERCOM1_SPI_Write( data1 , sizeof(data1));
//            SYSTICK_DelayMs(5);
//        }
//     }
//}

int main ( void )
{
    /* Initialize all modules */
    SYS_Initialize ( NULL );
    SYSTICK_TimerStart();
    SYSTICK_TimerPeriodSet(10000);
//    SERCOM1_SPI_CallbackRegister(callBack,0);
   
    while ( true )
    {
        /* Maintain state machines of all polled MPLAB Harmony modules. */
        SYS_Tasks ( );
       
        SERCOM1_SPI_Read( data , sizeof(data));
       // SERCOM5_USART_Write( data , sizeof(data));
        
        if((SERCOM1_REGS->SPIS.SERCOM_INTFLAG & SERCOM_SPIS_INTFLAG_DRE_Msk) == SERCOM_SPIS_INTFLAG_DRE_Msk){
         SERCOM1_SPI_Write( data1 , sizeof(data1));
         SYSTICK_DelayMs(100);
        } 
        
    }

    /* Execution should not come here during normal operation */

    return ( EXIT_FAILURE );
}


/*******************************************************************************
 End of File
*/

