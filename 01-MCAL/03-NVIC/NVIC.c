/********************************************************************************************/
/*									AUTHOR  : MIRA MOUSA	                                  								*/
/*									DATE    : MAR 10,2020                 	        			    		    			*/
/*									version : V2.0		  					      	                	    		        */
/********************************************************************************************/

#include "STD_Types.h"

#include "NVIC.h"
#include "NVIC_config.h"
//#include "cmsis_gcc.h"


#define NVIC_BASEADDRESS  0xE000E100
#define SCB_BASEADDRESS   0xE000E008


typedef struct
{
	u32 SETENA[8];        /* Interrupt Enable Registers */
	u32 _Reserved0[24];
	u32 CLRENA[8];        /* Interrupt Disable Registers */
	u32 _Reserved1[24];
	u32 SETPEND[8];       /* Interrupt Set-Pending Registers */
	u32 _Reserved2[24];
	u32 CLRPEND[8];       /* Interrupt Clear-Pending Registers */
	u32 _Reserved3[24];
	u32 ACTIVE[8];        /* Interrupt Active status registers */
	u32 _Reserved4[56];
	u8  PRI[240];         /* Interrupt Priority-Level Registers */
	u32 _Reserved5[644];
	u32 STIR;             /* Interrupt software trigger Register */
}NVIC_t;

#define NVIC            ((NVIC_t*)(NVIC_BASEADDRESS))
#define SCB_AIRCR       *((u32*)(SCB_BASEADDRESS+0x0C))

#define NVIC_NON_IMPLEMENTED_PRI  (u8)4




/*
 * Description   : This API shall Enable a specific interrupt
 * -> Parameters : Copy_u8IntNum (the interrupt number in vector table)
 * -> Return     : ERROR_S
 *                         ERROR_OK
 *                         ERROR_NOK
 */
ERROR_S NVIC_EnableInterrupt(u8 Copy_u8IntNum)
{

	u8 Local_u8RegNum = 0;
	u8 Local_u8BitNum;
	u8 Local_u8IntNum = Copy_u8IntNum;

	/* register number from 0 to 7 */
	while(Local_u8IntNum > 31)
	{
		Local_u8IntNum -= 31;
		Local_u8RegNum++;
	}
	/* interrupt bit number */
	Local_u8BitNum = Copy_u8IntNum - (32*Local_u8RegNum);
	/* Set the interrupt Enable bit */
	NVIC->SETENA[Local_u8RegNum] |= ((u32)1<<(u32)Local_u8BitNum);
	return ERROR_OK;
}

/*
 * Description   : This API shall Disable a specific interrupt
 * -> Parameters : Copy_u8IntNum (the interrupt number in vector table)
 * -> Return     : ERROR_S
 *                         ERROR_OK
 *                         ERROR_NOK
 */
ERROR_S NVIC_DisableInterrupt(u8 Copy_u8IntNum)
{
	u8 Local_u8RegNum = 0;
	u8 Local_u8BitNum;
	u8 Local_u8IntNum = Copy_u8IntNum;

	/* register number from 0 to 7 */
	while(Local_u8IntNum > 31)
	{
		Local_u8IntNum -= 31;
		Local_u8RegNum++;
	}
	/* interrupt bit number */
	Local_u8BitNum = Copy_u8IntNum - (32*Local_u8RegNum);
	/* Set the interrupt Disable bit */
	NVIC->CLRENA[Local_u8RegNum] |= ((u32)1<<(u32)Local_u8BitNum);
	return ERROR_OK;
}

/*
 * Description   : This API shall set interrupt's pending flag
 * -> Parameters : Copy_u8IntNum (the interrupt number in vector table)
 * -> Return     : ERROR_S
 *                         ERROR_OK
 *                         ERROR_NOK
 */
ERROR_S NVIC_SetPendingFlag(u8 Copy_u8IntNum)
{
	u8 Local_u8RegNum = 0;
	u8 Local_u8BitNum;
	u8 Local_u8IntNum = Copy_u8IntNum;

	/* register number from 0 to 7 */
	while(Local_u8IntNum > 31)
	{
		Local_u8IntNum -= 31;
		Local_u8RegNum++;
	}
	/* interrupt bit number */
	Local_u8BitNum = Copy_u8IntNum - (32*Local_u8RegNum);
	/* Set the interrupt set-pending flag*/
	NVIC->SETPEND[Local_u8RegNum] |= ((u32)1<<(u32)Local_u8BitNum);
	return ERROR_OK;
}

/*
 * Description   : This API shall clear interrupt's pending flag
 * -> Parameters : Copy_u8IntNum (the interrupt number in vector table)
 * -> Return     : ERROR_S
 *                         ERROR_OK
 *                         ERROR_NOK
 */
ERROR_S NVIC_ClearPendingFlag(u8 Copy_u8IntNum)
{
	u8 Local_u8RegNum = 0;
	u8 Local_u8BitNum;
	u8 Local_u8IntNum = Copy_u8IntNum;

	/* register number from 0 to 7 */
	while(Local_u8IntNum > 31)
	{
		Local_u8IntNum -= 31;
		Local_u8RegNum++;
	}
	/* interrupt bit number */
	Local_u8BitNum = Copy_u8IntNum - (32*Local_u8RegNum);
	/* clear the interrupt set-pending flag*/
	NVIC->CLRPEND[Local_u8RegNum] |= ((u32)1<<(u32)Local_u8BitNum);
	return ERROR_OK;
}

/*
 * Description   : This API shall set interrupt priority level
 * -> Parameters : Copy_u8GrpSubMask
 *                         NVIC_GROUPS_16_SUBGROUPS_0
 *                         NVIC_GROUPS_8_SUBGROUPS_2
 *                         NVIC_GROUPS_4_SUBGROUPS_4
 *                         NVIC_GROUPS_2_SUBGROUPS_8
 *                         NVIC_GROUPS_0_SUBGROUPS_16
 * -> Return     : ERROR_S
 *                         ERROR_OK
 *                         ERROR_NOK
 */
ERROR_S NVIC_SetPriGROUP(u8 Copy_u8GrpSubMask)
{
	SCB_AIRCR &= ~NVIC_STM_GROUP_SUBGROUP_MASK;
	SCB_AIRCR |= Copy_u8GrpSubMask;
	return ERROR_OK;
}

/*
 * Description   : This API shall set interrupt priority level
 * -> Parameters : *Copy_u8GrpSubMask
 * -> Return     : ERROR_S
 *                         ERROR_OK
 *                         ERROR_NOK
 */
ERROR_S NVIC_GetPriGROUP(u8 *Copy_u8GrpSubMask)
{
	*Copy_u8GrpSubMask = (u8)((SCB_AIRCR & NVIC_STM_GROUP_SUBGROUP_MASK) >> 7 );
	return ERROR_OK;
}

/*
 * Description   : This API shall set interrupt priority level
 * -> Parameters : Copy_u8IntNum (the interrupt number in vector table)
 *                 Copy_u8GroupPriority
 *                 Copy_u8SubPriority
 * -> Return     : ERROR_S
 *                         ERROR_OK
 *                         ERROR_NOK
 */
ERROR_S NVIC_SetPriorityLevel(u8 Copy_u8IntNum, u8 Copy_u8GroupPriority, u8 Copy_u8SubPriority)
{
	NVIC->PRI[Copy_u8IntNum] |= (Copy_u8SubPriority << NVIC_NON_IMPLEMENTED_PRI);
	NVIC->PRI[Copy_u8IntNum] |= (Copy_u8GroupPriority << (NVIC_NON_IMPLEMENTED_PRI + NVIC_SUBGROUP_BIT_SIZE));

	return ERROR_OK;
}

/*
 * Description   : This API shall Get interrupt priority level
 * -> Parameters : Copy_u8IntNum (the interrupt number in vector table)
 *                 Copy_u8PriorityLevel
 * -> Return     : ERROR_S
 *                         ERROR_OK
 *                         ERROR_NOK
 */
ERROR_S NVIC_GetPriorityLevel(u8 Copy_u8IntNum, u8 *Copy_u8PriorityLevel)
{
	*Copy_u8PriorityLevel = NVIC->PRI[Copy_u8IntNum] >> NVIC_NON_IMPLEMENTED_PRI ;

	return ERROR_OK;
}

/*
 * Description   : This API shall get interrupt active flag
 * -> Parameters : Copy_u8IntNum (the interrupt number in vector table)
 *                 *Copy_u8ActiveFlag
 * -> Return     : ERROR_S
 *                         ERROR_OK
 *                         ERROR_NOK
 */
ERROR_S NVIC_GetActiveStatus(u8 Copy_u8IntNum, u8 *Copy_u8ActiveFlag)
{
	u8 Local_u8RegNum = 0;
	u8 Local_u8BitNum;
	u8 Local_u8IntNum = Copy_u8IntNum;

	/* register number from 0 to 7 */
	while(Local_u8IntNum > 31)
	{
		Local_u8IntNum -= 31;
		Local_u8RegNum++;
	}
	/* interrupt bit number */
	Local_u8BitNum = Copy_u8IntNum - (32*Local_u8RegNum);

	*Copy_u8ActiveFlag = NVIC->ACTIVE[Local_u8RegNum] & (1 << Local_u8BitNum);

	return ERROR_OK;
}

/*
 * Description   : This API shall disable all exceptions except NMI and HARD Fault
 * -> Parameters : void
 * -> Return     : ERROR_S
 *                         ERROR_OK
 *                         ERROR_NOK
 */
ERROR_S NVIC_DisableExternalExceptions(void)
{
    asm("CPSID I");
	/*__set_PRIMASK(1);*/
	return ERROR_OK;
}

/*
 * Description   : This API shall enable all exceptions except NMI and HARD Fault
 * -> Parameters : void
 * -> Return     : ERROR_S
 *                         ERROR_OK
 *                         ERROR_NOK
 */
ERROR_S NVIC_EnableExternalExceptions(void)
{
    asm("CPSIE I");
	/*__set_PRIMASK(0);*/
	return ERROR_OK;
}

/*
 * Description   : This API shall disable all exceptions even HARD Fault except NMI
 * -> Parameters : void
 * -> Return     : ERROR_S
 *                         ERROR_OK
 *                         ERROR_NOK
 */
ERROR_S NVIC_DisableAllExceptions(void)
{
    asm("CPSID F");
	/*__set_FAULTMASK(1);*/
	return ERROR_OK;
}

/*
 * Description   : This API shall enable all exceptions even HARD Fault except NMI
 * -> Parameters : void
 * -> Return     : ERROR_S
 *                         ERROR_OK
 *                         ERROR_NOK
 */
ERROR_S NVIC_EnableAllExceptions(void)
{
    asm("CPSIE F");
	/*__set_FAULTMASK(0);*/
	return ERROR_OK;
}

/*
 * Description   : This API shall disable interrupt only with priority lower than Base Priority
 * -> Parameters : Copy_u32BasePriority
 * -> Return     : ERROR_S
 *                         ERROR_OK
 *                         ERROR_NOK
 */
ERROR_S NVIC_SetBasePriority(u32 Copy_u32BasePriority)
{
	/*__set_BASEPRI_MAX(Copy_u32BasePriority);*/
    asm("MSR basepri, %0" : : "r" ((u32)Copy_u32BasePriority) : "memory");


	return ERROR_OK;
}





















