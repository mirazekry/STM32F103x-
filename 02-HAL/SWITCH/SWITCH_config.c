/********************************************************************************************/
/*									AUTHOR  : MIRA MOUSA	                                  								*/
/*									DATE    : MAR 31,2020                 	        			    		    			*/
/*									version : V1.0		  					      	                	    		        */
/********************************************************************************************/

#include "STD_Types.h"

#include "GPIO.h"
#include "SWITCH.h"
#include "SWITCH_config.h"

switch_t Switches_info[NUM_OF_SWITCHES] = {
		{PIN5, GPIOB , PIN_SET,SWITCH_NOT_PRESSED}
};

