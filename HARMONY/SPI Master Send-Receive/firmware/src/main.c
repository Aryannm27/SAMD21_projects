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

//uint8_t data[128];
//uint8_t rec[128];
//uint8_t rx[128];


uint8_t dSend = 'A';
uint8_t dRecv;

int main(void) {
    /* Initialize all modules */

    SYS_Initialize(NULL);
    SYSTICK_TimerStart();
    SYSTICK_TimerPeriodSet(10000);
  
  //  LED_Clear();

//    for(int i=0;i<=128;i++)
//    {
//        rx[i]=128-i;
//    }
//      
//    for(int i=0;i<=128;i++)
//    {
//        data[i]=i;
//    }
    
    
    while (true) {
        /* Maintain state machines of all polled MPLAB Harmony modules. */
        SYS_Tasks();
        
//        uint8_t count=0;
//        LED_Clear();
   
        SS_Clear();
//        for (int i = 0;i<=sizeof(rx);i++)
//        {

            SERCOM1_SPI_WriteRead(&dSend, sizeof(uint8_t), &dRecv, sizeof(uint8_t));
            SERCOM5_USART_Write(&dRecv, sizeof(dRecv));
            SS_Set();  
//            if( rx[i] == dRecv )
//            {
//                count++;
//            }
//     
            if(dRecv == 'B')
            {
                 LED_Set();
            }
            else
            {
                LED_Clear();
            }
            
          
        } 
        
      
    /* Execution should not come here during normal operation */
    return ( EXIT_FAILURE);
}


/*******************************************************************************
 End of File
 */

