/************************************************************************************/
/*  Author  :  Mira Mousa                                                           */
/*  Version :  01                                                                   */
/*  Date    :  15 Jan 2020                                                          */
/************************************************************************************/

#include "STD_Types.h"

#include "RCC.h"



/*  function status */
typedef enum
{
	STATE_OK,
	STATE_NOK
}State;


State state;
/************************************************************************************/
/*  defining RCC registers using structure method                                   */
/************************************************************************************/
typedef struct
{
	u32 CR;        //RCC_CR
	u32 CFGR;      //RCC_CFGR
	u32 CIR;       //RCC_CIR
	u32 APB2RSTR;  //RCC_APB2RSTR
	u32 APB1RSTR;  //RCC_APB1RSTR
	u32 AHBENR;    //RCC_AHBRSTR
	u32 APB2ENR;   //RCC_APB2ENR
	u32 APB1ENR;   //RCC_APB1ENR
	u32 BDCR;      //RCC_BDCR
	u32 CSR;       //RCC_CSR
}RCC_Prepheral;

#define RCC ((RCC_Prepheral*)0x40021000)



/*  Description : This API configure Enable and Disable High Speed Clock Source          */
u8 RCC_u8HSClockCtrl(u8 Copy_u8Clockname,u8 Copy_u8State ,u8 Copy_u8ClockRDY)
{
	state = STATE_NOK;
	/*	Enabling the clock source*/
	if(Copy_u8State)
	{
		/*	Set the clock on bit */
		RCC->CR |= Copy_u8Clockname;
		/*	Check the clock ready bit till rise
		 * to make sure the clock is enabled*/
		while(!(RCC->CR & Copy_u8ClockRDY));
		state = STATE_OK;
	}
	else
	{
		/*	Clear the clock on bit */
		RCC->CR &= ~Copy_u8Clockname;
		/*	Check the clock ready bit till clear
		 *to make sure the Clock is disabled	*/
		while(RCC->CR & Copy_u8ClockRDY);
		state = STATE_OK;
	}
	return state;
}


/*  Description : This API configure system clock source Switch               */
u8 RCC_u8ClockSource(u8 Copy_u8Clockname,u8 Copy_u8SysClkState)
{
	state = STATE_NOK;
	/*Clear System clock switch bits*/
	RCC->CFGR &= CLK_CLR;
	/*Select System clock switch name*/
	RCC->CFGR |= Copy_u8Clockname;
	/*Check if the clock is selected*/
	if((RCC->CFGR & Copy_u8SysClkState) == Copy_u8SysClkState )
	{
		state = STATE_OK;
	}
	return state;
}

/*  Description : This API configure PLL clock select                               */
void RCC_voidPLLSRC(u8 Copy_u8Clockname,u8 Copy_u8MulOrDiv,u8 Copy_u8Operation)
{
	/*Check if it HSI or HSE*/
	if(HSI == Copy_u8Clockname)
	{
		/*Clear PLL CLK source bit to choose HSI*/
		RCC->CFGR &= PLLSRCHSI;
	}
	else
	{
		/*SET PLL CLK source bit to choose HSE*/
		RCC->CFGR |= PLLSRCHSE;
	}

	/*Check for operation to be done on the clock*/
	if((DIV == Copy_u8MulOrDiv))
	{
		/*Clear for no Division */
		RCC->CFGR &= PLL_HSEPRE;
		/*Applying factor mask*/
		RCC->CFGR |= Copy_u8Operation;
	}
	else
	{
		/*Clear for applying the mask */
		RCC->CFGR &= PLLMUL_CLR;
		/*Applying factor mask*/
		RCC->CFGR |= Copy_u8Operation;
	}

}


/*  Description : This API configure Enabling nd Disabling Low Speed Clock Source        */
u8 RCC_u8LSClockCtrl(u8 Copy_u8Clockname,u8 Copy_u8State ,u8 Copy_u8ClockRDY)
{
	state = STATE_NOK;
	if(LSEON == Copy_u8Clockname)
	{
		/*	Enabling the clock source*/
		if(Copy_u8State)
		{
			/*	Set the clock on bit */
			RCC->BDCR |= Copy_u8Clockname;
			/*	Check the clock ready bit till rise
			 * to make sure the clock is enabled*/
			while(!(RCC->BDCR & Copy_u8ClockRDY));
			state = STATE_OK;
		}
		else
		{
			/*	Clear the clock on bit */
			RCC->BDCR &= ~Copy_u8Clockname;
			/*	Check the clock ready bit till clear
			 *to make sure the Clock is disabled	*/
			while(RCC->BDCR & Copy_u8ClockRDY);
			state = STATE_OK;
		}
	}
	else
	{
		if(Copy_u8State)
		{
			/*	Set the clock on bit */
			RCC->CSR |= Copy_u8Clockname;
			/*	Check the clock ready bit till rise
			 * to make sure the clock is enabled*/
			while(!(RCC->CSR & Copy_u8ClockRDY));
			state = STATE_OK;
		}
		else
		{
			/*	Clear the clock on bit */
			RCC->CSR &= ~Copy_u8Clockname;
			/*	Check the clock ready bit till clear
			 *to make sure the Clock is disabled	*/
			while(RCC->CSR & Copy_u8ClockRDY);
			state = STATE_OK;
		}
	}
	return state;
}


/*  Description : This API Enable prepheral clock                                              */
extern u8 RCC_u8PrephiralEnable(u8 Copy_u8Bus, u8 Copy_u8PreName)
{
  state = STATE_NOK;
  switch(Copy_u8Bus)
  {
    case AHB:
      RCC->AHBENR  |= Copy_u8PreName;
      state = STATE_OK;
      break;
    case APB2:
      RCC->APB2ENR |= Copy_u8PreName;
      state = STATE_OK;
      break;
    case APB1:
      RCC->APB1ENR |= Copy_u8PreName;
      state = STATE_OK;
      break;
  }
  return state;
}


/*  Description : This API disable prepheral clock                                              */
extern u8 RCC_u8PrephiralDisable(u8 Copy_u8Bus, u8 Copy_u8PreName)
{
  state = STATE_NOK;
  switch(Copy_u8Bus)
  {
    case AHB:
      RCC->AHBENR  &= ~Copy_u8PreName;
      state = STATE_OK;
      break;
    case APB2:
      RCC->APB2ENR &= ~Copy_u8PreName;
      state = STATE_OK;
      break;
    case APB1:
      RCC->APB1ENR &= ~Copy_u8PreName;
      state = STATE_OK;
      break;
  }
  return state;
}
