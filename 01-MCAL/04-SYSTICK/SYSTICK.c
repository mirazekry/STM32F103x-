/********************************************************************************************/
/*									AUTHOR  : MIRA MOUSA	                                  								*/
/*									DATE    : MAR 20,2020                 	        			    		    			*/
/*									version : V1.0		  					      	                	    		        */
/********************************************************************************************/

#include "STD_Types.h"
#include "SYSTICK.h"
#include "SYSTICK_config.h"

#define SYSTICK_BASEADDRESS             0xE000E010

typedef struct 
{
    /* data */
    u32 CTRL;   /*control and status register*/
    u32 LOAD;   /*Reload value register*/
    u32 VAL;    /*current value register*/
    u32 CALIB;  /*calibration value register*/
}SYSTICK_t;

#define SYSTICK                         ((volatile SYSTICK_t*)SYSTICK_BASEADDRESS)
#define NULL 							(void*)(0)

static SYSTICK_Cbf_t CallBackFunction = NULL;


/*SYSTICK APIs defination*/

/*
 * Description  : This API shall Initiate Systick peripheral 
 * Parameters   : None
 * Return       : ERROR_S
 *                      ERROR_OK
 *                      ERROR_NOK
 */
ERROR_S SYSTICK_Init(void)
{
    ERROR_S Local_ErrorStatus = ERROR_NOK;
    /*initiating the systick clock source as it is configuired
     *if it is free running clock AHB
     * or it is External referance clock AHB/8 
     * and the NOREF bit in calibration register is not high (there is an external reference clock)
     */
    if(SYSTICK_PRE_AHB8 == SYSTICK_CLKSOURCE && !(SYSTICK->CALIB & SYSTICK_NOREF))
    {
        SYSTICK->CTRL &= SYSTICK_CLKSOURCE;
        Local_ErrorStatus = ERROR_OK;
    }
    else if(SYSTICK_PRE_AHB == SYSTICK_CLKSOURCE)
    {
        SYSTICK->CTRL |= SYSTICK_CLKSOURCE;
        Local_ErrorStatus = ERROR_OK;
    }
    else
    {
        Local_ErrorStatus = ERROR_NOK;
    }

    /*
     *intiatizing the interrupt Enable/Diasble bit as it is configuired
     *it can be Enabled by the user or Disabled though changing its
     *value from SYSTICK_config.h
     */
    if (SYSTICK_INTERRUPT_ENABLE == SYSTICK_INTERRUPT)
    {
        SYSTICK->CTRL |= SYSTICK_INTERRUPT;
    }
    else
    {
        SYSTICK->CTRL &= SYSTICK_INTERRUPT;
    }
    if((SYSTICK->CTRL & SYSTICK_INTERRUPT_ENABLE) == SYSTICK_INTERRUPT)
    {
        Local_ErrorStatus = ERROR_OK;
    }

    /*clearing Current value register*/
    SYSTICK->VAL = ~SYSTICK_CURRENT_VAL_MASK;


    return Local_ErrorStatus; 
}

/*
 * Description  : This API shall Start the Systick timer (counter) 
 * Parameters   : None
 * Return       : ERROR_S
 *                      ERROR_OK
 *                      ERROR_NOK
 */
ERROR_S SYSTICK_Start(void)
{
    ERROR_S Local_ErrorStatus = ERROR_NOK;
    /*set the enable bit in the control register*/
    SYSTICK->CTRL |= SYSTICK_ENABLE;
    Local_ErrorStatus = ERROR_OK;

    return Local_ErrorStatus;
}

/*
 * Description  : This API shall Stop the Systick timer (counter)
 * Parameters   : None
 * Return       : ERROR_S
 *                      ERROR_OK
 *                      ERROR_NOK
 */
ERROR_S SYSTICK_Stop(void)
{
    ERROR_S Local_ErrorStatus = ERROR_NOK;
    /*clear the enable bit in the control register*/
    SYSTICK->CTRL &= SYSTICK_DISABLE;
    Local_ErrorStatus = ERROR_OK;

    return Local_ErrorStatus;
}
/*
 * Description  : This API shall Set the systick reload value 
 * Parameters   : timeUs (time in microseconds)
 * Return       : ERROR_S
 *                      ERROR_OK
 *                      ERROR_NOK
 */
ERROR_S SYSTICK_SetTime(u32 Copy_u32timeUs,const u8 Systick_clksrc_MHZ)
{
    ERROR_S Local_ErrorStatus = ERROR_NOK;
    /*u32 Local_u32Reload;*/

    /*In STM the value in TENMS in the calibraion register when loaded to the current value register 
     *will fire the interrupt after 1ms(1000Us) interval so it can be used in calculating the wanted interval
     */
    /*the TENMS value can give 1000 Ms interval so we can calculate the reload value from the wanted interval*/
    /*Local_u32Reload = ((SYSTICK->CALIB & SYSTICK_TENMS)*Copy_u32timeUs)/1000;*/

    /*LOAD the RELOAD value to the Reload register value*/
    /*SYSTICK->LOAD = Local_u32Reload & SYSTICK_RELOAD_VAL_MASK;*/

    /*check if the value was loaded*/
    /*
    if((SYSTICK->LOAD == Local_u32Reload) & SYSTICK_RELOAD_VAL_MASK)
    {
        Local_ErrorStatus = ERROR_OK;
    }
    */

    /*SYSTICK->LOAD = (Copy_u32timeUs*(Systick_clksrc_MHZ/8)) ;*/
    SYSTICK->LOAD = Copy_u32timeUs;
    Local_ErrorStatus = ERROR_OK;
    
    return Local_ErrorStatus;
}

/*
 * Description  : This API shall Set the systick callback function 
 * Parameters   : Cbf
 * Return       : ERROR_S
 *                      ERROR_OK
 *                      ERROR_NOK
 */
ERROR_S SYSTICK_SetCallBack(SYSTICK_Cbf_t   Copy_Cbf)
{
    ERROR_S Local_ErrorStatus = ERROR_NOK;

    /*check if the call back function wanted not equal NULL */
    if(Copy_Cbf)
    {
        CallBackFunction = Copy_Cbf;
        Local_ErrorStatus = ERROR_OK;
    }   
    return Local_ErrorStatus;
}



void SysTick_Handler(void)
{
    /*Check if the call back function is not NULL*/
    if(CallBackFunction)
    {
        CallBackFunction();
    }
}
