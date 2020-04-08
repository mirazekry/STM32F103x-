/********************************************************************************************/
/*									AUTHOR  : MIRA MOUSA	                                  								*/
/*									DATE    : MAR 31,2020                 	        			    		    			*/
/*									version : V1.0		  					      	                	    		        */
/********************************************************************************************/

#include "STD_Types.h"

#include "RCC.h"
#include "GPIO.h"
#include "SWITCH.h"
#include "SWITCH_config.h"
#include "diag/Trace.h"



extern  switch_t Switches_info[NUM_OF_SWITCHES];
volatile Pin Switch_pins[NUM_OF_SWITCHES];



/*
 * Description :  This API shall init the Switch pin ,port and satus
 * Parameters  : void
 * Return 	   : ERROR_S
 * 						ERROR_OK
 * 						ERROR_NOK
 */
ERROR_S Switch_Init(void)
{
	u8 i ;
	for(i=0 ; i<NUM_OF_SWITCHES;i++)
	{
		Switch_pins[i].pin		=	Switches_info[i].pin;
		Switch_pins[i].speed 	= 	SWITCH_SPEED;
		switch(Switches_info[i].mode)
		{
		case PIN_RESET:
			Switch_pins[i].mode = INPUT_PULLUP;
			break;
		case PIN_SET:
			Switch_pins[i].mode = INPUT_PULLDOWN;
			break;
		default:
			return ERROR_NOK;
		}
		RCC_u8PrephiralEnable(APB2, Switches_info[i].port);
		GPIO_INIT(Switches_info[i].port ,Switch_pins[i]);
	}
	return ERROR_OK;
}

/*
 * Description :  This API shall get the Switch current state
 * Parameters  : *Copy_SwitchName
 * Return 	   : ERROR_S
 * 						ERROR_OK
 * 						ERROR_NOK
 */
ERROR_S Switch_Get_SwitchStatus(u8 Copy_u8PortName, Pin Copy_SwitchName, u8 *Copy_u8State)
{
	GPIO_GetPinVal(Copy_u8PortName, Copy_SwitchName, Copy_u8State);

	return ERROR_OK;
}

/*
 * The runnable switch task to control the switch behaviour
 */
void Switch_vTask(void)
{
	u8 i ;
	u8 CurrentState;
	static u8 PrevState[NUM_OF_SWITCHES]	=	{0};
	static u8 counter[NUM_OF_SWITCHES]		=	{0};

	//trace_printf("ana a3ml eh b2aa\n");


	for(i=0;i<NUM_OF_SWITCHES;i++)
	{
		Switch_Get_SwitchStatus(Switches_info[i].port ,Switch_pins[i] ,&Switches_info[i].state);
		CurrentState = (Switches_info[i].mode ^ Switches_info[i].state);
		if(CurrentState == PrevState[i])
		{
			counter[i]++;
		}
		else
		{
			counter[i]				=	0;
		}

		if(counter[i] == 5)
		{
			Switches_info[i].state 	= 	CurrentState;
			counter[i] 				= 	0;
			/*if(Switches_info[i].state == SWITCH_PRESSED)
			{
				GPIO_SetPinVal(GPIOB,Switch_pins[i],1);
			}*/

		}
		PrevState[i]				=	CurrentState;
	}

}




















