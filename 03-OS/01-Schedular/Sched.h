/********************************************************************************************/
/*									AUTHOR  : MIRA MOUSA	                                  								*/
/*									DATE    : MAR 28,2020                 	        			    		    			*/
/*									version : V1.0		  					      	                	    		        */
/********************************************************************************************/

#ifndef _SCHED_H_
#define _SCHED_H_



/*pointer to function runnable*/
typedef void(*taskRunnable_t)(void);

/*Task control block*/
typedef struct{
	taskRunnable_t runnable;
	u32 periodicTime;
	u32 priority;
}TCB;

/*Schedular APIs defination*/

/*
 *Description : This API shall creat task control block and allocate it in task array
 *Parameters  : Copy_TCB
 *Return      : ERROR_S
 *					ERROR_OK
 *					ERROR_NOK
 */
/*extern ERROR_S Sched_CreateTask(TCB *Copy_TCB);*/

/*
 *Description : This API shall initiate the schedular timer (last to be called  in the system) and tasks
 *Parameters  : void
 *Return      : ERROR_S
 *					ERROR_OK
 *					ERROR_NOK
 */
extern ERROR_S Sched_Init(void);

/*
 *Description : This API shall start schedular
 *Parameters  : void
 *Return      : ERROR_S
 *					ERROR_OK
 *					ERROR_NOK
 */
extern void Sched_Start(void);

/*
 *Description : This API shall susbend 
 *Parameters  : Copy_TCB
 *Return      : ERROR_S
 *					ERROR_OK
 *					ERROR_NOK
 */
extern ERROR_S Sched_SusbendTask(TCB *Copy_TCB);

/*
 *Description : This API shall stop the schedular 
 *Parameters  : Copy_TCB
 *Return      : ERROR_S
 *					ERROR_OK
 *					ERROR_NOK
 */
extern ERROR_S Sched_Sleep(void);

#endif
