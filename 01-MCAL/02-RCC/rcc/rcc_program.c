#include "std_types.h"
#include "bit_math.h"
#include "rcc_config.h"
#include "rcc_private.h"
#include "rcc_register.h"
#include "rcc_interface.h"


u8 rcc_u8Clock (u8 clockSource)
{
	u8 status=0;
	switch(clockSource)
	{
		case HSI_VAL:
			SET_BIT(RCC->CR,HSION);
			while(GET_BIT(RCC->CR,HSIRDY)!=1);
			RCC->CFGR &=~(0b11<<SW_PIN);
			RCC->CFGR |= (HSI_VAL<<SW_PIN);
			CLEAR_BIT(RCC->CR,PLLON);
			CLEAR_BIT(RCC->CR,HSEON);
			if(HSI_VAL==GET_BIT(RCC->CFGR,SWS_PIN))
			{
				status=1;
			}
			break;
			
		case HSE_VAL:
			SET_BIT(RCC->CR,HSEON);
			while(GET_BIT(RCC->CR,HSERDY)!=1);
			RCC->CFGR &=~(0b11<<SW_PIN);
			RCC->CFGR |= (HSE_VAL<<SW_PIN);
			CLEAR_BIT(RCC->CR,PLLON);
			CLEAR_BIT(RCC->CR,HSION);
			if(HSE_VAL==GET_BIT(RCC->CFGR,SWS_PIN))
			{
				status=1;
			}
			break;
			
		case PLL_VAL:
			SET_BIT(RCC->CR,PLLON);
			while(GET_BIT(RCC->CR,PLLRDY)!=1);
			RCC->CFGR &=~(0b11<<SW_PIN);
			RCC->CFGR |= (PLL_VAL<<SW_PIN);
			if(PLL_VAL==GET_BIT(RCC->CFGR,SWS_PIN))					//has the operation been done succesfully??
			{
				status=1;
			}
			break;
		default:
			status=0;										//if the clocksource is  not equal any number of the defined numbers
		
	}
	return status;
}

u8 rcc_u8PllEnable (u8 pllmul, u8 pllsrc)
{
	u8 Loc_status=0;
	if (pllsrc == HSEDIV2_check)
	{
		u8 srcStatus = rcc_u8Clock(HSE_VAL);						
		SET_BIT(RCC->CFGR,PLLXTPRE);									//USE HSE/2

	}
	else
	{
		u8 srcStatus = rcc_u8Clock(pllsrc);						//HSE or HSI
		if(pllsrc == HSE)
		{
			CLEAR_BIT(RCC->CFGR,PLLXTPRE);
		}
	}
	
	if (srcStatus!=1)		
	{
		return Loc_status;
	}
	
	
	RCC->CFGR &=~ (0b1111<<PLLMUL);
	RCC->CFGR |= (pllmul<<PLLMUL);
	
	Loc_status = rcc_u8Clock(PLL_VAL);
	return Loc_status;

}

void rcc_voidEnablePeripheral (u8 peripheral)
{
	if(peripheral<32)
	{
		SET_BIT(RCC->AHBENR,peripheral);
	}
	else if(peripheral >= 32 && peripheral<64)
	{
		peripheral = peripheral-32;
		SET_BIT(RCC->APB2ENR,peripheral);
	}
	else if(peripheral >= 64 && peripheral<96)
	{
		peripheral = peripheral-64;
		SET_BIT(RCC->APB1ENR,peripheral);
	}
}

void rcc_voidDisablePeripheral (u8 peripheral)
{
	if(peripheral<32)
	{
		CLEAR_BIT(RCC->AHBENR,peripheral);
	}
	else if(peripheral >= 32 && peripheral<64)
	{
		peripheral = peripheral-32;
		CLEAR_BIT(RCC->APB2ENR,peripheral);
	}
	else if(peripheral >= 64 && peripheral<96)
	{
		peripheral = peripheral-64;
		CLEAR_BIT(RCC->APB1ENR,peripheral);
	}
}

void rcc_setMCO(u8 mcosrc)
{
	
}

void rcc_AHBprescaler(u8 prescaler)
{
	
}

void rcc_APB2prescaler(u8 prescaler)
{
	
}

void rcc_APB1prescaler(u8 prescaler)
{
	
}
