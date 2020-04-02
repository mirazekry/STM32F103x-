/********************************************************************************************/
/*									AUTHOR  : MIRA MOUSA	                                  								*/
/*									DATE    : MAR 28,2020                 	        			    		    			*/
/*									version : V1.0		  					      	                	    		        */
/********************************************************************************************/

#include "STD_Types.h"
#include "Sched.h"
#include "Sched_cfg.h"



/*application tasks' prototypes*/
extern TCB app_1;
extern TCB app_2;

#define NULL 	(*void)0

/*this array prototype should exist in program.c*/

 SysTaskInfo_t systaskInfo[NUM_TASK]	=
{
		{&app_1,0},
		{&app_2,0}
};

