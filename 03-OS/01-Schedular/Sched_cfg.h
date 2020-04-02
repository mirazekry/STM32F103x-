/********************************************************************************************/
/*									AUTHOR  : MIRA MOUSA	                                  								*/
/*									DATE    : MAR 28,2020                 	        			    		    			*/
/*									version : V1.0		  					      	                	    		        */
/********************************************************************************************/

#ifndef _SCHED_CFG_H_
#define _SCHED_CFG_H_

/*system task info block*/
typedef struct{
	TCB *appTask;
	u32   delayTicks;
}SysTaskInfo_t;

#define		TICKTIMEms					10
#define 	NUM_TASK					2
#define 	SYSTICK_RELOAD_VALUE		(TICKTIMEms*1000)

#endif
