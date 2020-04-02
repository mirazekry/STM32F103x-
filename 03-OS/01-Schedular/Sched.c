/********************************************************************************************/
/*									AUTHOR  : MIRA MOUSA	                                  								*/
/*									DATE    : MAR 28,2020                 	        			    		    			*/
/*									version : V1.0		  					      	                	    		        */
/********************************************************************************************/

#include "STD_Types.h"

#include "Sched.h"
#include "Sched_cfg.h"

#include "SYSTICK.h"
#include "SYSTICK_config.h"

/*System task block*/
typedef struct{
	TCB *appTask;
	u32 RemainToExec;
	u32 periodTicks;
	u8 state;
}SysTask_t;

/*task states*/
#define 	ACTIVE 		1
#define 	SUSBENDED 	0

/*system tasks' info block array declaration*/
extern SysTaskInfo_t systaskInfo[NUM_TASK];

static	SysTask_t systasks[NUM_TASK];

volatile  u8 OSflag = 0;
volatile  u8 awake;

/*
 *Description : This API shall creat task control block and allocate it in task array
 *Parameters  : Copy_TCB
 *Return      : ERROR_S
 *					ERROR_OK
 *					ERROR_NOK
 */
ERROR_S Sched_CreateTask(TCB *Copy_TCB)
{
	if(Copy_TCB)
	{
		systasks[Copy_TCB->priority].appTask = Copy_TCB;
		systasks[Copy_TCB->priority].periodTicks = (Copy_TCB->periodicTime/TICKTIMEms);

	}
	else
	{
		return ERROR_NOK;
	}
	return ERROR_OK;
}


/*systick callback function*/
void SetOsFlag(void)
{
	OSflag = 1;
}


/*
 *Description : This API shall initiate the schedular timer (last to be called  in the system) and tasks
 *Parameters  : void
 *Return      : ERROR_S
 *					ERROR_OK
 *					ERROR_NOK
 */
extern ERROR_S Sched_Init(void)
{
	u32 i;
	awake = 1;
	for(i=0;i<NUM_TASK;i++)
	{
		systaskInfo[i].appTask->priority = i;
		Sched_CreateTask(systaskInfo[i].appTask);
		systasks[i].RemainToExec = systaskInfo[i].delayTicks;
		systasks[i].periodTicks = systasks[i].appTask->periodicTime / TICKTIMEms;
		systasks[i].state =	ACTIVE; 
	}
	SYSTICK_Init();
	SYSTICK_SetCallBack(SetOsFlag);
	SYSTICK_SetTime(SYSTICK_RELOAD_VALUE);
	SYSTICK_Start();
	return ERROR_OK;
}


/*
 *Description : This API shall start schedular
 *Parameters  : void
 *Return      : ERROR_S
 *					ERROR_OK
 *					ERROR_NOK
 */
extern void Sched_Start(void)
{
	static u32 i;
	while(awake)
	{
		if(OSflag)
		{
			OSflag = 0;
			for(i=0;i<NUM_TASK;i++)
			{
				if((systasks[i].RemainToExec == 0) && systasks[i].state)
				{
					systasks[i].appTask->runnable();
					systasks[i].RemainToExec = systasks[i].periodTicks;
				}
				systasks[i].RemainToExec--;
			}
		}
	}
}

/*
 *Description : This API shall susbend 
 *Parameters  : Copy_TCB
 *Return      : ERROR_S
 *					ERROR_OK
 *					ERROR_NOK
 */
extern ERROR_S Sched_SusbendTask(TCB *Copy_TCB)
{
	systasks[Copy_TCB->priority].state = SUSBENDED;
	return ERROR_OK;
}

/*
 *Description : This API shall stop the schedular 
 *Parameters  : Copy_TCB
 *Return      : ERROR_S
 *					ERROR_OK
 *					ERROR_NOK
 */
extern ERROR_S Sched_Sleep(void)
{
	awake = 0;
	return ERROR_OK;
}



