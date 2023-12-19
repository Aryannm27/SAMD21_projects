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
#define ANALOG_REFERENCE 5.0 

float sampleADC = 0;
const int UD ;          
const int INC ;          
const int CS ;  

void ADC()
{
  ADC_ConversionStart();
  float sampleADC = ADC_ConversionResultGet();
  float volts = ( sampleADC * ANALOG_REFERENCE )/1024.0;
  printf("volts : %f ",volts);
}

void X9C103PINC(int CS,int INC){
    INC_Set();
    SYSTICK_DelayMs(10);         
    CS_Clear();
    INC_Clear();
    SYSTICK_DelayMs(10);
    CS_Set();   
    SYSTICK_DelayMs(200);
}

int main ( void )
{
    SYS_Initialize ( NULL );
    SYSTICK_TimerStart();
    SYSTICK_TimerPeriodSet(10000);
    ADC_Enable();

    while(true)
    {
        SYS_Tasks();
        for(int i=32;i>0;i--){
        UD_Clear();
        ADC();
        X9C103PINC(CS,INC);
        }
        for(int i=0;i<32;i++){
        UD_Set();
        ADC();
        X9C103PINC(CS,INC);
        }
    }
    
        return ( EXIT_FAILURE );
}

/*******************************************************************************
 End of File
*/

