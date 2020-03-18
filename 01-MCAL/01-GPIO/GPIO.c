/********************************************************************************************/
/*									AUTHOR  : MIRA MOUSA									*/
/*									DATE    : Feb 26 ,2020									*/
/*									version : V1.0											*/
/********************************************************************************************/

#include "STD_Types.h"
#include "GPIO.h"


/*	
 *	Description :	GPIO Ports Registers Base Addresses	
 */
#define GPIO_BASEADDRESS	0x40010800
/*
#define GPIO_PORTA		0x40010800	
#define GPIO_PORTB		0x40010C00
#define GPIO_PORTC		0x40011000
#define GPIO_PORTD		0x40011400
#define GPIO_PORTE		0x40011800
#define GPIO_PORTF		0x40011C00
#define GPIO_PORTG		0x40012000
 */

/*	
 *	Description :	This Structure Defines the map of 
 *	GPIOx Ports' Control registers	
 */
typedef struct  
{
	u32 CRL;
	u32 CRH;
	u32 IDR;
	u32 ODR;
	u32 BSRR;
	u32 BRR;
	u32 LCKR;
	u32 dummy[249];
}GPIO_CTRL;

/*	Description :	The Ports section in the memory	    	*/
#define  GPIO	((volatile GPIO_CTRL*)GPIO_BASEADDRESS)
//#define  GPIOA ((volatile GPIO_CTRL*)GPIO_PORTA)
//#define  GPIOB ((volatile GPIO_CTRL*)GPIO_PORTB)
//#define  GPIOC ((volatile GPIO_CTRL*)GPIO_PORTC)
//#define  GPIOD ((volatile GPIO_CTRL*)GPIO_PORTD)
//#define  GPIOE ((volatile GPIO_CTRL*)GPIO_PORTE)
//#define  GPIOF ((volatile GPIO_CTRL*)GPIO_PORTF)
//#define  GPIOG ((volatile GPIO_CTRL*)GPIO_PORTG)


#define MODE_BITCAP			(u8)4

#define registerBitCap			7


/*	
 *	Description :	This API initiate and Select the mode Of 
 *	a Selected pin.
 *	->	PARAMETERS Pin PIN
 *	port		--> GPIO_A...B,C,D,E,F,G
 *	PIN->pinNum	--> no. of pins
 *	PIN->PIN	-->	PIN0..,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15
 *	PIN->MODE	-->	INPUT_FLOATING		,INPUT_PULLUP		,INPUT_PULLDOWN
 *					INPUT_ANALOG		,OUTPUT_OPENDRAIN	,OUTPUT_PUSHPULL	
 *					AF_PUSHPULL		,AF_OPENDRAIN		
 *	->	RETURN ERROR_S --> ERROR_NOK ,ERROR_OK
 */
ERROR_S GPIO_INIT(u8 port,Pin PIN)
{
	ERROR_S State = ERROR_NOK;
	u8 shiftamount = 0;
	u16 pinCheck = PIN.pin;

	/*	looping on the pins value to set their mode	*/
	while(pinCheck != 0)
	{
		if(PIN_SET==(pinCheck & 0x01))
		{
			if(shiftamount <= registerBitCap)
			{
				//	1- Clear pin mode bits
				(GPIO+port)->CRL &= ~(MODE_MASK<<(shiftamount*MODE_BITCAP));
				//	2- Configure the mode bits and set Pin mode value
				(GPIO+port)->CRL |=  (PIN.mode<<(shiftamount*MODE_BITCAP));
				//	3- Configure the speed bits and set Pin mode value
				(GPIO+port)->CRL |=  (PIN.speed<<(shiftamount*MODE_BITCAP));
				//	4- Check if the value was added successfully
				if (((GPIO+port)->CRL & ~(MODE_MASK<<(shiftamount*MODE_BITCAP))>>(shiftamount*MODE_BITCAP)) == (PIN.mode | PIN.speed))
				{
					State = ERROR_OK;
				}
			}
			else
			{
				//	1- Clear pin mode bits
				(GPIO+port)->CRH &= ~(MODE_MASK<<((shiftamount-8)*MODE_BITCAP));
				//	2- Configure the mode bits and set Pin mode value
				(GPIO+port)->CRH |=  (PIN.mode<<((shiftamount-8)*MODE_BITCAP));
				//	3- Configure the speed bits and set Pin mode value
				(GPIO+port)->CRH |=  (PIN.speed<<((shiftamount-8)*MODE_BITCAP));
				//	4- Check if the value was added successfully
				if (((GPIO+port)->CRH & ~(MODE_MASK<<((shiftamount-8)*MODE_BITCAP))>>((shiftamount-8)*MODE_BITCAP)) == (PIN.mode | PIN.speed))
				{
					State = ERROR_OK;
				}
			}
		}
		shiftamount ++;
		pinCheck = pinCheck >> 1;
	}

	return State;
}


/*	
 *	Description :	This API shall set the Value of the pin on the 
 *	Selected pin.
 *  ->	PARAMETERS Pin PIN , u8 PinVal
 *	PIN->Port	--> GPIO_A...B,C,D,E,F,G
 *	PIN->pin	-->	PIN0..,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15
 *	PIN->mode	-->	INPUT_FLOATING		,INPUT_PULLUP		,INPUT_PULLDOWN
 *					INPUT_ANALOG		,OUTPUT_OPENDRAIN	,OUTPUT_PUSHPULL
 *					AF_PUSHPULL		,AF_OPENDRAIN
 *	PinVal	-->	PIN_SET ,PIN_RESET
 *	->	Return ERROR_S --> ERROR_NOK ,ERROR_OK
 */
ERROR_S GPIO_SetPinVal(u8 port ,Pin PIN ,u8 PinVal)
{
	ERROR_S State = ERROR_NOK;
	u8 shiftamount = 0;
	u16 pinCheck = PIN.pin;

	/*	looping on the pins value to set their mode	*/
	while(pinCheck)
	{
		/*	check for the pins which is defined in PIN->pin	*/
		if(PIN_SET==(pinCheck & 0x01))
		{
			/*	check for the  pin value	*/
			if (PIN_SET == PinVal)
			{
				(GPIO+port)->BSRR |= ( PIN_SET << shiftamount );
				if ((GPIO+port)->ODR & (PIN_SET << shiftamount))
				{
					State = ERROR_OK;	
				}
			}
			else
			{
				(GPIO+port)->BRR |= ( PIN_SET << shiftamount );
				if (!((GPIO+port)->ODR & (PIN_SET << shiftamount)))
				{
					State = ERROR_OK;
				}
			}
		}
		shiftamount ++;
		pinCheck = pinCheck >> 1;
	}

	return State;
}


/*	
 *	Description :	This API shall get the Value of the pin on the 
 *	Selected pin.
 *  ->	PARAMETERS Pin PIN , u8 PinVal
 *	PIN->Port	--> GPIO_A...B,C,D,E,F,G
 *	PIN->pin	-->	PIN0..,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15
 *	PIN->mode	-->	INPUT_FLOATING		,INPUT_PULLUP		,INPUT_PULLDOWN
 *					INPUT_ANALOG		,OUTPUT_OPENDRAIN	,OUTPUT_PUSHPULL
 *					AF_PUSHPULL		,AF_OPENDRAIN
 *	*PinVal	-->	The PinVal is the value returned from the pin
 *	->	Return ERROR_S --> ERROR_NOK ,ERROR_OK
 */
ERROR_S GPIO_GetPinVal(u8 port,Pin PIN,u8 *PinVal)
{
	ERROR_S State = ERROR_NOK;
	u8 shiftamount = 0;
	u16 pinCheck = PIN.pin;

	/*	looping on the pins value to set their mode	*/
	while(pinCheck)
	{
		/*	check for the pins which is defined in PIN->pin	*/
		if(PIN_SET==(pinCheck & 0x01))
		{
			*PinVal = (u8)(((GPIO+port)->IDR & (PIN_SET<<shiftamount)) >> shiftamount);
			if (*PinVal == (u8)(((GPIO+port)->IDR & (PIN_SET<<shiftamount)) >> shiftamount))
			{
				State = ERROR_OK;
			}
		}
		shiftamount ++;
		pinCheck = pinCheck >> 1;
	}
	return State;
}
