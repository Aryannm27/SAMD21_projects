/*******************************************************************************
  TCC Peripheral Library Interface Source File

  Company
    Microchip Technology Inc.

  File Name
    plib_tcc3.c

  Summary
    TCC3 peripheral library source file.

  Description
    This file implements the interface to the TCC peripheral library.  This
    library provides access to and control of the associated peripheral
    instance.

*******************************************************************************/

// DOM-IGNORE-BEGIN
/*******************************************************************************
* Copyright (C) 2018 Microchip Technology Inc. and its subsidiaries.
*
* Subject to your compliance with these terms, you may use Microchip software
* and any derivatives exclusively with Microchip products. It is your
* responsibility to comply with third party license terms applicable to your
* use of third party software (including open source software) that may
* accompany Microchip software.
*
* THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER
* EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED
* WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A
* PARTICULAR PURPOSE.
*
* IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE,
* INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND
* WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS
* BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO THE
* FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS IN
* ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF ANY,
* THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.
*******************************************************************************/
// DOM-IGNORE-END


// *****************************************************************************
// *****************************************************************************
// Section: Included Files
// *****************************************************************************
// *****************************************************************************

/*  This section lists the other files that are included in this file.
*/
#include "interrupts.h"
#include "plib_tcc3.h"



/* Initialize TCC module */
void TCC3_PWMInitialize(void)
{
    /* Reset TCC */
    TCC3_REGS->TCC_CTRLA = TCC_CTRLA_SWRST_Msk;
    while ((TCC3_REGS->TCC_SYNCBUSY & TCC_SYNCBUSY_SWRST_Msk) != 0U)
    {
        /* Wait for sync */
    }
    /* Clock prescaler */
    TCC3_REGS->TCC_CTRLA = TCC_CTRLA_PRESCALER_DIV8 ;
    TCC3_REGS->TCC_WEXCTRL = TCC_WEXCTRL_OTMX(0UL);
    /* Dead time configurations */
    TCC3_REGS->TCC_WEXCTRL |= TCC_WEXCTRL_DTIEN0_Msk | TCC_WEXCTRL_DTIEN1_Msk | TCC_WEXCTRL_DTIEN2_Msk | TCC_WEXCTRL_DTIEN3_Msk
 	 	 | TCC_WEXCTRL_DTLS(64UL) | TCC_WEXCTRL_DTHS(64UL);

    TCC3_REGS->TCC_WAVE = TCC_WAVE_WAVEGEN_NPWM;

    /* Configure duty cycle values */
    TCC3_REGS->TCC_CC[0] = 0U;
    TCC3_REGS->TCC_CC[1] = 0U;
    TCC3_REGS->TCC_CC[2] = 0U;
    TCC3_REGS->TCC_CC[3] = 1000U;
    TCC3_REGS->TCC_PER = 2399U;



    while (TCC3_REGS->TCC_SYNCBUSY != 0U)
    {
        /* Wait for sync */
    }
}


/* Start the PWM generation */
void TCC3_PWMStart(void)
{
    TCC3_REGS->TCC_CTRLA |= TCC_CTRLA_ENABLE_Msk;
    while ((TCC3_REGS->TCC_SYNCBUSY & TCC_SYNCBUSY_ENABLE_Msk) != 0U)
    {
        /* Wait for sync */
    }
}

/* Stop the PWM generation */
void TCC3_PWMStop (void)
{
    TCC3_REGS->TCC_CTRLA &= ~TCC_CTRLA_ENABLE_Msk;
    while ((TCC3_REGS->TCC_SYNCBUSY & TCC_SYNCBUSY_ENABLE_Msk) != 0U)
    {
        /* Wait for sync */
    }
}

/* Configure PWM period */
bool TCC3_PWM24bitPeriodSet (uint32_t period)
{
    bool status = false;
    if ((TCC3_REGS->TCC_STATUS & (TCC_STATUS_PERBV_Msk)) == 0U)
    {
        TCC3_REGS->TCC_PERB = period & 0xFFFFFFU;
        status = true;
    }    
    return status;
}


/* Read TCC period */
uint32_t TCC3_PWM24bitPeriodGet (void)
{
    while ((TCC3_REGS->TCC_SYNCBUSY & TCC_SYNCBUSY_PER_Msk) != 0U)
    {
        /* Wait for sync */
    }
    return (TCC3_REGS->TCC_PER & 0xFFFFFFU);
}

/* Configure dead time */
void TCC3_PWMDeadTimeSet (uint8_t deadtime_high, uint8_t deadtime_low)
{
    TCC3_REGS->TCC_WEXCTRL &= ~(TCC_WEXCTRL_DTHS_Msk | TCC_WEXCTRL_DTLS_Msk);
    TCC3_REGS->TCC_WEXCTRL |= TCC_WEXCTRL_DTHS((uint32_t)deadtime_high) | TCC_WEXCTRL_DTLS((uint32_t)deadtime_low);
}

bool TCC3_PWMPatternSet(uint8_t pattern_enable, uint8_t pattern_output)
{
    bool status = false;
    if ((TCC3_REGS->TCC_STATUS & (TCC_STATUS_PATTBV_Msk)) == 0U)
    {
        TCC3_REGS->TCC_PATTB = (uint16_t)(pattern_enable | ((uint32_t)pattern_output << 8U));
        status = true;
    }   
    return status; 
}


/* Set the counter*/
void TCC3_PWM24bitCounterSet (uint32_t count)
{
    TCC3_REGS->TCC_COUNT = count & 0xFFFFFFU;
    while ((TCC3_REGS->TCC_SYNCBUSY & TCC_SYNCBUSY_COUNT_Msk) != 0U)
    {
        /* Wait for sync */
    }
}

/* Enable forced synchronous update */
void TCC3_PWMForceUpdate(void)
{
    TCC3_REGS->TCC_CTRLBSET |= (uint8_t)TCC_CTRLBCLR_CMD_UPDATE;
    while ((TCC3_REGS->TCC_SYNCBUSY & TCC_SYNCBUSY_CTRLB_Msk) != 0U)
    {
        /* Wait for sync */
    }
}

/* Enable the period interrupt - overflow or underflow interrupt */
void TCC3_PWMPeriodInterruptEnable(void)
{
    TCC3_REGS->TCC_INTENSET = TCC_INTENSET_OVF_Msk;
}

/* Disable the period interrupt - overflow or underflow interrupt */
void TCC3_PWMPeriodInterruptDisable(void)
{
    TCC3_REGS->TCC_INTENCLR = TCC_INTENCLR_OVF_Msk;
}

/* Read interrupt flags */
uint32_t TCC3_PWMInterruptStatusGet(void)
{
    uint32_t interrupt_status;
    interrupt_status = TCC3_REGS->TCC_INTFLAG;
    /* Clear interrupt flags */
    TCC3_REGS->TCC_INTFLAG = interrupt_status;
    return interrupt_status;
}


/**
 End of File
*/
