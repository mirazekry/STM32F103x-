/********************************************************************************************/
/*									AUTHOR  : MIRA MOUSA	                                  								*/
/*									DATE    : April 2,2020                 	        			    		    			*/
/*									version : V1.0		  					      	                	    		        */
/********************************************************************************************/

#include "STD_Types.h"
#include "GPIO.h"
#include "LCD_cfg.h"
#include "LCD.h"

#include "diag/Trace.h"


/*LCD initialization comleted flag*/
u8 LCD_u8InitComplete;

u8 LCD_u8UserWord[LCD_MAX_DATA_BUFFER_LEN];
u8 LCD_u8UserWordLength;
u8 LCD_u8CurrentCMD;
u8 LCD_u8Row;
u8 LCD_u8Col;

#define LCD_INIT_COMPLETED    0
#define LCD_INIT_INPROGRESS   1

/*
 * Processes Stages
 */
typedef enum {
	FunctionSet_1,  //00111100
	FunctionSet_2,  //00111100
	FunctionSet_3,  //00111100
	FunctionSet_4,  //00111100
	DisplayON_OFF,//00001000
	DisplayClear, //00000001
	EntryModeSet,  //00000110
	DisplayON_OFF_2,//00001000
}InitStages_t;

/*
 * Write Stages
 */
typedef enum {
	Stage1,
	Stage2
}WriteStages_t;

/*
 * processes states
 */
typedef enum{
	Idle_Process,
	WriteDATA_Process,
	WriteCMD_Process,
	Clear_Process,
	CursorMove_Process
}process_t;

static process_t LCD_CurrentProcess;
static WriteStages_t LCD_Write_Stage = Stage1;
static InitStages_t  LCD_Init_Stage = FunctionSet_1;

#define FUNCTION_SET      (u8)0b00110000
#define FUNCTION_SET_2    (u8)0b00111000
#define DISPLAY_ON_OFF    (u8)0b00001000
#define DISPLAY_CLEAR     (u8)0b00000001
#define ENTRY_MODE_SET    (u8)0b00000110
#define DISPLAY_ON_OFF_2  (u8)0b00001100

Pin LCD_DataPins[LCD_BIT_MODE] = {
		{LCD_GPIO_D0_PIN,SPEED_50,OUTPUT_PUSHPULL},
		{LCD_GPIO_D1_PIN,SPEED_50,OUTPUT_PUSHPULL},
		{LCD_GPIO_D2_PIN,SPEED_50,OUTPUT_PUSHPULL},
		{LCD_GPIO_D3_PIN,SPEED_50,OUTPUT_PUSHPULL},
		{LCD_GPIO_D4_PIN,SPEED_50,OUTPUT_PUSHPULL},
		{LCD_GPIO_D5_PIN,SPEED_50,OUTPUT_PUSHPULL},
		{LCD_GPIO_D6_PIN,SPEED_50,OUTPUT_PUSHPULL},
		{LCD_GPIO_D7_PIN,SPEED_50,OUTPUT_PUSHPULL}
};

Pin LCD_CTRLPins[3]               = {
		{LCD_GPIO_EN_PIN,SPEED_50,OUTPUT_PUSHPULL},
		{LCD_GPIO_RW_PIN,SPEED_50,OUTPUT_PUSHPULL},
		{LCD_GPIO_RS_PIN,SPEED_50,OUTPUT_PUSHPULL}
};
/***********************************************************************************/


/************************/
/*Processes Definitions */
/************************/
static void LCD_Init_Process(void);
static void LCD_WriteDATA_Process(void);
static void LCD_WriteCMD_Process(void);
static void LCD_ClearProcess(void);
static void LCD_GOTO_Process(void);



/********************************************************************************/
/*********************************User APPLICATION APIs *************************/

/*
 *Description : This API shall configure the LCD GPIO Data and control pins
 *Parameters  : void
 *Return      : return status
 *                  STATE_OK
 *                  STATE_BUSY
 *                  STATE_ERROR
 */
u8 LCD_Config(void)
{
	u8 idx;
	/*GPIO Configuration , set pin speed and output push/pull mode*/
	for(idx=0 ; idx<LCD_BIT_MODE ; idx++)
	{
		GPIO_INIT(LCD_GPIO_DATA_PORT, LCD_DataPins[idx]);
	}
	for(idx=0 ; idx<3 ; idx++)
	{
		GPIO_INIT(LCD_GPIO_CTRL_PORT, LCD_CTRLPins[idx]);
	}



	/*Initialize all pins to zero*/
	for(idx=0 ; idx<LCD_BIT_MODE ; idx++)
	{
		GPIO_SetPinVal(LCD_GPIO_DATA_PORT, LCD_DataPins[idx] , PIN_RESET);
	}
	for(idx=0 ; idx<3 ; idx++)
	{
		GPIO_SetPinVal(LCD_GPIO_CTRL_PORT, LCD_CTRLPins[idx] , PIN_RESET);
	}

	LCD_u8InitComplete = LCD_INIT_INPROGRESS;
	return STATE_OK;
}

/*
 *Description : This API shall change the process state to write process
 *Parameters  : Copy_u8word , Copy_u8Length
 *Return      : return status
 *                  STATE_OK
 *                  STATE_BUSY
 *                  STATE_ERROR
 */
u8 LCD_WriteDATA(const u8 * Copy_u8word ,u8 Copy_u8Length)
{
	u8 idx;
	u8 ERROR_S = STATE_ERROR;

	if(LCD_CurrentProcess == Idle_Process)
	{
		LCD_CurrentProcess = WriteDATA_Process;

		for(idx = 0 ; idx < Copy_u8Length ; idx++)
		{
			LCD_u8UserWord[idx] = Copy_u8word[idx];
		}

		LCD_u8UserWordLength = Copy_u8Length;

		ERROR_S = STATE_OK;
	}
	else
	{
		ERROR_S = STATE_BUSY;
	}
	return ERROR_S;
}


/*
 *Description : This API shall change the Process state to Write command process
 *Parameters  : Copy_u8Cmd
 *Return      : return status
 *                  STATE_OK
 *                  STATE_BUSY
 *                  STATE_ERROR
 */
u8 LCD_WriteCMD(const u8 Copy_u8Cmd)
{
	u8 ERROR_S = STATE_ERROR;

	if(LCD_CurrentProcess == Idle_Process)
	{
		LCD_CurrentProcess = WriteCMD_Process;

		LCD_u8CurrentCMD = Copy_u8Cmd;

		ERROR_S = STATE_OK;
	}
	else
	{
		ERROR_S = STATE_BUSY;
	}
	return ERROR_S;
}


/*
 *Description : This API shall change the Process state to Clear process
 *Parameters  : void
 *Return      : return status
 *                  STATE_OK
 *                  STATE_BUSY
 *                  STATE_ERROR
 */
u8 LCD_Clear(void)
{
	u8 ERROR_S = STATE_ERROR;
	if(LCD_CurrentProcess == Idle_Process)
	{
		LCD_CurrentProcess = Clear_Process;

		ERROR_S = STATE_OK;
	}
	else
	{
		ERROR_S = STATE_BUSY;
	}

	return ERROR_S;
}

/*
 *Description : This API shall change the process state to curserMove process
 *Parameters  :  Copy_u8PosX  ,Copy_u8PosY
 *Return      : return status
 *                  STATE_OK
 *                  STATE_BUSY
 *                  STATE_ERROR
 */
extern u8 LCD_GOTO(u8 Copy_u8PosX, u8 Copy_u8PosY)
{
	u8 ERROR_S = STATE_ERROR;
	if(LCD_CurrentProcess == Idle_Process)
	{
		LCD_CurrentProcess = CursorMove_Process;

		LCD_u8Row = Copy_u8PosY;
		LCD_u8Col = Copy_u8PosX;

		ERROR_S = STATE_OK;
	}
	else
	{
		ERROR_S = STATE_BUSY;
	}

	return ERROR_S;
}


/*
 *Description : The runnable task of LCD comes every 2ms
 */
void LCD_Task(void)
{
	//trace_printf("f 7yatyyyy\n ");
	if(LCD_u8InitComplete == LCD_INIT_COMPLETED)
	{
		switch(LCD_CurrentProcess)
		{
		case Idle_Process:
			break;
		case WriteDATA_Process:
			LCD_WriteDATA_Process();
			break;
		case WriteCMD_Process:
			LCD_WriteCMD_Process();
			break;
		case Clear_Process:
			LCD_ClearProcess();
			break;
		case CursorMove_Process:
			LCD_GOTO_Process();
			break;
		}
	}
	else
	{
		LCD_Init_Process();
	}
}



/**********************************************************************************/
/*************************************Task Processes*******************************/


static void LCD_Init_Process(void)
{
	static u8 StageFlag = 0;
	if(LCD_u8InitComplete == LCD_INIT_COMPLETED)
	{
		LCD_CurrentProcess = Idle_Process;
	}
	else
	{
		switch(LCD_Init_Stage)
		{
		case FunctionSet_1:
			LCD_u8CurrentCMD = FUNCTION_SET;
			if(StageFlag == 0 || StageFlag == 1)
			{
				LCD_WriteCMD_Process();
			}
			if(StageFlag==3)
			{
				LCD_Init_Stage = FunctionSet_2;
				StageFlag = 0;
			}
			else
			{
				StageFlag++;
			}
			break;

		case FunctionSet_2:
			LCD_u8CurrentCMD = FUNCTION_SET;
			if(StageFlag == 0 || StageFlag == 1)
			{
				LCD_WriteCMD_Process();
			}
			if(StageFlag==3)
			{
				LCD_Init_Stage = FunctionSet_3;
				StageFlag = 0;
			}
			else
			{
				StageFlag++;
			}
			break;

		case FunctionSet_3:
			LCD_u8CurrentCMD = FUNCTION_SET;
			if(StageFlag == 0 || StageFlag == 1)
			{
				LCD_WriteCMD_Process();
			}
			if(StageFlag==3)
			{
				LCD_Init_Stage = FunctionSet_4;
				StageFlag = 0;
			}
			else
			{
				StageFlag++;
			}
			break;

		case FunctionSet_4:
			LCD_u8CurrentCMD = FUNCTION_SET_2;
			if(StageFlag == 0 || StageFlag == 1)
			{
				LCD_WriteCMD_Process();
			}
			if(StageFlag==3)
			{
				LCD_Init_Stage = DisplayON_OFF;
				StageFlag = 0;
			}
			else
			{
				StageFlag++;
			}
			break;

		case DisplayON_OFF:
			LCD_u8CurrentCMD = DISPLAY_ON_OFF;
			if(StageFlag == 0 || StageFlag == 1)
			{
				LCD_WriteCMD_Process();
			}
			if(StageFlag==3)
			{
				LCD_Init_Stage = DisplayClear;
				StageFlag = 0;
			}
			else
			{
				StageFlag++;
			}
			break;
		case DisplayClear:
			if(StageFlag == 0 || StageFlag == 1)
			{
				LCD_ClearProcess();
			}
			if(StageFlag==3)
			{
				LCD_Init_Stage = EntryModeSet;
				StageFlag = 0;
			}
			else
			{
				StageFlag++;
			}
			break;
		case EntryModeSet:
			LCD_u8CurrentCMD = ENTRY_MODE_SET;
			if(StageFlag == 0 || StageFlag == 1)
			{
				LCD_WriteCMD_Process();
			}
			if(StageFlag==3)
			{
				LCD_Init_Stage = DisplayON_OFF_2;
				StageFlag = 0;
			}
			else
			{
				StageFlag++;
			}
			break;
		case DisplayON_OFF_2:
			LCD_u8CurrentCMD = DISPLAY_ON_OFF_2;
			if(StageFlag == 0 || StageFlag == 1)
			{
				LCD_WriteCMD_Process();
			}
			if(StageFlag==3)
			{
				LCD_Init_Stage = FunctionSet_1;
				LCD_u8InitComplete = LCD_INIT_COMPLETED;
				StageFlag = 0;
			}
			else
			{
				StageFlag++;
			}
			break;
		}
	}
}


static void LCD_WriteDATA_Process(void)
{
	/* Current word index */
	static u8 Local_u8DataIdx = 0;

	if(LCD_u8UserWordLength != 0)
	{
		if(LCD_Write_Stage == Stage1)
		{
			/*  Sending Rising edge */
			GPIO_SetPinVal(LCD_GPIO_CTRL_PORT,LCD_CTRLPins[0],PIN_SET);
			/*  RW pin LOW  */
			GPIO_SetPinVal(LCD_GPIO_CTRL_PORT,LCD_CTRLPins[1],PIN_RESET);
			/*  RS pin HIGH  */
			GPIO_SetPinVal(LCD_GPIO_CTRL_PORT,LCD_CTRLPins[2],PIN_SET);
			/*  Load Data bus */
			GPIO_SetPinVal(LCD_GPIO_DATA_PORT, LCD_DataPins[0], (LCD_u8UserWord[Local_u8DataIdx] & 0x01) >> 0);
			GPIO_SetPinVal(LCD_GPIO_DATA_PORT, LCD_DataPins[1], (LCD_u8UserWord[Local_u8DataIdx] & 0x02) >> 1);
			GPIO_SetPinVal(LCD_GPIO_DATA_PORT, LCD_DataPins[2], (LCD_u8UserWord[Local_u8DataIdx] & 0x04) >> 2);
			GPIO_SetPinVal(LCD_GPIO_DATA_PORT, LCD_DataPins[3], (LCD_u8UserWord[Local_u8DataIdx] & 0x08) >> 3);
			GPIO_SetPinVal(LCD_GPIO_DATA_PORT, LCD_DataPins[4], (LCD_u8UserWord[Local_u8DataIdx] & 0x10) >> 4);
			GPIO_SetPinVal(LCD_GPIO_DATA_PORT, LCD_DataPins[5], (LCD_u8UserWord[Local_u8DataIdx] & 0x20) >> 5);
			GPIO_SetPinVal(LCD_GPIO_DATA_PORT, LCD_DataPins[6], (LCD_u8UserWord[Local_u8DataIdx] & 0x40) >> 6);
			GPIO_SetPinVal(LCD_GPIO_DATA_PORT, LCD_DataPins[7], (LCD_u8UserWord[Local_u8DataIdx] & 0x80) >> 7);

			/* increament the Current word index */
			Local_u8DataIdx++;

			/* change the write stage */
			LCD_Write_Stage = Stage2;
		}
		else if(LCD_Write_Stage == Stage2)
		{
			/* Sending faling edge */
			GPIO_SetPinVal(LCD_GPIO_CTRL_PORT,LCD_CTRLPins[0],PIN_RESET);

			/* change the write stage */
			LCD_Write_Stage = Stage1;

			/* decrement the buffer length */
			LCD_u8UserWordLength--;
		}
	}
	else
	{
		/* Reset the write stage */
		LCD_Write_Stage = Stage1;

		/* reset back Current word index */
		Local_u8DataIdx = 0;

		/* change current process to idle process */
		LCD_CurrentProcess = Idle_Process;
	}
}


static void LCD_WriteCMD_Process(void)
{

	if(LCD_Write_Stage == Stage1)
	{
		/*  Sending Rising edge */
		GPIO_SetPinVal(LCD_GPIO_CTRL_PORT,LCD_CTRLPins[0],PIN_SET);
		/*  RW pin LOW  */
		GPIO_SetPinVal(LCD_GPIO_CTRL_PORT,LCD_CTRLPins[1],PIN_RESET);
		/*  RS pin LOW  */
		GPIO_SetPinVal(LCD_GPIO_CTRL_PORT,LCD_CTRLPins[2],PIN_RESET);
		/*  Load Data bus */
		GPIO_SetPinVal(LCD_GPIO_DATA_PORT, LCD_DataPins[0], (LCD_u8CurrentCMD & 0x01) >> 0);
		GPIO_SetPinVal(LCD_GPIO_DATA_PORT, LCD_DataPins[1], (LCD_u8CurrentCMD & 0x02) >> 1);
		GPIO_SetPinVal(LCD_GPIO_DATA_PORT, LCD_DataPins[2], (LCD_u8CurrentCMD & 0x04) >> 2);
		GPIO_SetPinVal(LCD_GPIO_DATA_PORT, LCD_DataPins[3], (LCD_u8CurrentCMD & 0x08) >> 3);
		GPIO_SetPinVal(LCD_GPIO_DATA_PORT, LCD_DataPins[4], (LCD_u8CurrentCMD & 0x10) >> 4);
		GPIO_SetPinVal(LCD_GPIO_DATA_PORT, LCD_DataPins[5], (LCD_u8CurrentCMD & 0x20) >> 5);
		GPIO_SetPinVal(LCD_GPIO_DATA_PORT, LCD_DataPins[6], (LCD_u8CurrentCMD & 0x40) >> 6);
		GPIO_SetPinVal(LCD_GPIO_DATA_PORT, LCD_DataPins[7], (LCD_u8CurrentCMD & 0x80) >> 7);


		/* change the write stage */
		LCD_Write_Stage = Stage2;
	}
	else if(LCD_Write_Stage == Stage2)
	{
		/* Sending faling edge */
		GPIO_SetPinVal(LCD_GPIO_CTRL_PORT,LCD_CTRLPins[0],PIN_RESET);

		/* change the write stage */
		LCD_Write_Stage = Stage1;

		/* change current process to idle process */
		LCD_CurrentProcess = Idle_Process;
	}
}


static void LCD_ClearProcess(void)
{
	/* load user command with diplay clear command */
	LCD_u8CurrentCMD = DISPLAY_CLEAR;
	/* run the Write command process */
	LCD_WriteCMD_Process();
}

static void LCD_GOTO_Process(void)
{
	switch(LCD_u8Row)
	{
	case LCD_FIRST_ROW:
		LCD_u8CurrentCMD = LCD_FIRST_ROW + LCD_u8Col;
		LCD_WriteCMD_Process();
		break;
	case LCD_SCND_ROW:
		LCD_u8CurrentCMD = LCD_SCND_ROW + LCD_u8Col;
		LCD_WriteCMD_Process();
		break;
	}
}

