/********************************************************************************************/
/*									AUTHOR  : MIRA MOUSA	                                  								*/
/*									DATE    : MAR 31,2020                 	        			    		    			*/
/*									version : V1.0		  					      	                	    		        */
/********************************************************************************************/

#ifndef _SWITCH_H_
#define _SWITCH_H_


/*Switch type block*/
typedef struct
{
	u32 pin;
	u32 port;
	u8  mode;
	u8 state;
}switch_t;


/*state options*/
#define SWITCH_PRESSED		1
#define SWITCH_NOT_PRESSED  0


/*
 * Description :  This API shall init the Switch pin ,port and satus
 * Parameters  : void
 * Return 	   : ERROR_S
 * 						ERROR_OK
 * 						ERROR_NOK
 */
extern ERROR_S Switch_Init(void);

/*
 * Description :  This API shall get the Switch current state
 * Parameters  : Copy_u8PortName ,Copy_SwitchName , *Copy_u8State
 * Return 	   : ERROR_S
 * 						ERROR_OK
 * 						ERROR_NOK
 */
extern ERROR_S Switch_Get_SwitchStatus(u8 Copy_u8PortName, Pin Copy_SwitchName, u8 *Copy_u8State);

/*
 * The runnable switch task to control the switch behaviour
 */
extern void Switch_vTask(void);



#endif
