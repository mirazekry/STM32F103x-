/********************************************************************************************/
/*									AUTHOR  : MIRA MOUSA	                                  								*/
/*									DATE    : MAR 20,2020                 	        			    		    			*/
/*									version : V1.0		  					      	                	    		        */
/********************************************************************************************/

#ifndef _SYSTICK_H_
#define _SYSTICK_H_

/* Type of a pointer type to a callback function */
typedef     void(*SYSTICK_Cbf_t)(void);

/***************Driver used Masks*****************/
/*SYSTICK Control and Status Register bit MASKs*/
#define SYSTICK_ENABLE                  (u32)0x00000001
#define SYSTICK_DISABLE                 (u32)0xFFFFFFFE
#define SYSTICK_INTERRUPT_ENABLE        (u32)0x00000002
#define SYSTICK_INTERRUPT_DISABLE       (u32)0xFFFFFFFD
#define SYSTICK_PRE_AHB8   		        (u32)0xFFFFFFFB
#define SYSTICK_PRE_AHB			        (u32)0x00000004
#define SYSTICK_COUNTFLAG_MASK          (u32)0x00000010

/*SYSTICK Reload Value Register Mask*/
#define SYSTICK_RELOAD_VAL_MASK         (u32)0x00FFFFFF

/*SYSTICK Current Value Register Mask*/
#define SYSTICK_CURRENT_VAL_MASK        (u32)0x00FFFFFF

/*SYSTICK Calibration Value Register Masks*/
#define SYSTICK_NOREF                   (u32)0x80000000
#define SYSTICK_SKEW                    (u32)0x40000000
#define SYSTICK_TENMS                   (u32)0x00FFFFFF

/**************** SYSTICK APIs ************************/
/*
 * Description  : This API shall Initiate Systick peripheral 
 * Parameters   : None
 * Return       : ERROR_S
 *                      ERROR_OK
 *                      ERROR_NOK
 */
extern ERROR_S SYSTICK_Init(void);
/*
 * Description  : This API shall Start the Systick timer (counter) 
 * Parameters   : None
 * Return       : ERROR_S
 *                      ERROR_OK
 *                      ERROR_NOK
 */
extern ERROR_S SYSTICK_Start(void);
/*
 * Description  : This API shall Set the systick reload value 
 * Parameters   : timeUs (time in microseconds),Systick_clksrc_MHZ
 * Return       : ERROR_S
 *                      ERROR_OK
 *                      ERROR_NOK
 */
extern ERROR_S SYSTICK_SetTime(u32 Copy_u32timeUs,const u8 Systick_clksrc_MHZ);
/*
 * Description  : This API shall Set the systick callback function 
 * Parameters   : Cbf
 * Return       : ERROR_S
 *                      ERROR_OK
 *                      ERROR_NOK
 */
extern ERROR_S SYSTICK_SetCallBack(SYSTICK_Cbf_t   Copy_Cbf);
/*
 * Description  : This API shall Stop the Systick timer (counter) 
 * Parameters   : None
 * Return       : ERROR_S
 *                      ERROR_OK
 *                      ERROR_NOK
 */
extern ERROR_S SYSTICK_Stop(void);

#endif
