/* ************************************************************************** */
/** Descriptive File Name

  @Company
    Company Name

  @File Name
    filename.c

  @Summary
    Brief description of the file.

  @Description
    Describe the purpose of this file.
 */
/* ************************************************************************** */

/* ************************************************************************** */
/* ************************************************************************** */
/* Section: Included Files                                                    */
/* ************************************************************************** */
/* ************************************************************************** */

bool SOM_UART01SEND(void *buffer, const size_t size)
{   
    if(SERCOM2_USART_Write( void *buffer, const size_t size ))
    {
       return true;
    }
    else
    {
       return false;
    }
    
}


/* *****************************************************************************
 End of File
 */
