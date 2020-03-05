/********************************************************************************************/
/*									AUTHOR  : MIRA MOUSA									*/
/*									DATE    : Feb 26 ,2020									*/
/*									version : V1.0											*/
/********************************************************************************************/




/*	
 *	Description :	This section Defines the available pin's 
 *	modes in STM32F10x
 */
#define MODE_MASK					(u8)0b1111

#define INPUT_FLOATING				(u8)0b0100
#define INPUT_PULLUP				(u8)0b1000
#define INPUT_PULLDOWN				(u8)0b1000
#define INPUT_ANALOG				(u8)0b0000
										 
#define OUTPUT_OPENDRAIN			(u8)0b0100
#define OUTPUT_PUSHPULL				(u8)0b0000
#define AF_PUSHPULL					(u8)0b1000
#define AF_OPENDRAIN				(u8)0b1100

#define SPEED_0						(u8)0b0000
#define SPEED_10					(u8)0b0001
#define SPEED_2						(u8)0b0010
#define SPEED_50					(u8)0b0011


/*	
 *	Description :	This section Defines the number of pins on port
 */
#define PIN0						(u16)0x0001
#define PIN1						(u16)0x0002
#define PIN2						(u16)0x0004
#define PIN3						(u16)0x0008
#define PIN4						(u16)0x0010
#define PIN5						(u16)0x0020
#define PIN6						(u16)0x0040
#define PIN7						(u16)0x0080
#define PIN8						(u16)0x0100
#define PIN9						(u16)0x0200
#define PIN10						(u16)0x0400
#define PIN11						(u16)0x0800
#define PIN12						(u16)0x1000
#define PIN13						(u16)0x2000
#define PIN14						(u16)0x4000
#define PIN15						(u16)0x8000



/*	
 *	Description :	This section Defines the ports' names 
 */
#define GPIOA						(u8)0
#define GPIOB						(u8)1
#define GPIOC						(u8)2
#define GPIOD						(u8)3
#define GPIOE						(u8)4
#define GPIOF						(u8)5
#define GPIOG						(u8)6

/*	
 *	Description :	This section Defines the Pin's Values
 */
#define PIN_SET						(u8)1
#define PIN_RESET					(u8)0

/*	
 *	Description :	This section Defines the Pin's Prosperities
 */
typedef struct
{
	u16	pin;
	u8	speed;
	u8	mode;
}Pin;

/*	
 *	Description :	This section is The Declaration of the APIs 
 *	used in this Drive
 */

/*	
 *	Description :	This API initiate and Select the mode Of 
 *	a Selected pin.
 *	->	PARAMETERS Pin PIN
 *	port		--> GPIO_A...B,C,D,E,F,G
 *	PIN->PIN	-->	PIN0..,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15
 *	PIN->speed	--> SPEED_0		,SPEED_10	,SPEED_2	,SPEED_50
 *	PIN->MODE	-->	INPUT_FLOATING		,INPUT_PULLUP		,INPUT_PULLDOWN
 *					INPUT_ANALOG		,OUTPUT_OPENDRAIN	,OUTPUT_PUSHPULL	
 *					AF_PUSHPULL		,AF_OPENDRAIN		
 *	->	RETURN ERROR_S --> ERROR_NOK ,ERROR_OK
 */
extern ERROR_S GPIO_INIT(u8 port,Pin PIN);

/*	
 *	Description :	This API shall set the Value of the pin on the 
 *	Selected pin.
 *  ->	PARAMETERS Pin PIN , u8 PinVal
 *	Port		--> GPIO_A...B,C,D,E,F,G
 *	PIN->pin	-->	PIN0..,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15
 *	PIN->speed	--> SPEED_0		,SPEED_10	,SPEED_2	,SPEED_50
 *	PIN->mode	-->	INPUT_FLOATING		,INPUT_PULLUP		,INPUT_PULLDOWN
 *					INPUT_ANALOG		,OUTPUT_OPENDRAIN	,OUTPUT_PUSHPULL
 *					AF_PUSHPULL		,AF_OPENDRAIN
 *	PinVal	-->	PIN_SET ,PIN_RESET
 *	->	Return ERROR_S --> ERROR_NOK ,ERROR_OK
 */
extern ERROR_S GPIO_SetPinVal(u8 port,Pin PIN,u8 PinVal);

/*	
 *	Description :	This API shall get the Value of the pin on the 
 *	Selected pin.
 *  ->	PARAMETERS Pin PIN , u8 PinVal
 *	Port		--> GPIO_A...B,C,D,E,F,G
 *	PIN->pin	-->	PIN0..,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15
 *	PIN->speed	--> SPEED_0		,SPEED_10	,SPEED_2	,SPEED_50
 *	PIN->mode	-->	INPUT_FLOATING		,INPUT_PULLUP		,INPUT_PULLDOWN
 *					INPUT_ANALOG		,OUTPUT_OPENDRAIN	,OUTPUT_PUSHPULL
 *					AF_PUSHPULL		,AF_OPENDRAIN
 *	*PinVal	-->	The PinVal is the value returned from the pin
 *	->	Return ERROR_S --> ERROR_NOK ,ERROR_OK
 */
extern ERROR_S GPIO_GetPinVal(u8 port,Pin PIN,u8 *PinVal);
