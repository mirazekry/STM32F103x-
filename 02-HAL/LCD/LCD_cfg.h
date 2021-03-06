/********************************************************************************************/
/*									AUTHOR  : MIRA MOUSA	                                  								*/
/*									DATE    : April 2,2020                 	        			    		    			*/
/*									version : V1.0		  					      	                	    		        */
/********************************************************************************************/


#ifndef _LCD_CFG_H_
#define _LCD_CFG_H_

#define     LCD_BIT_MODE                 8

#define     LCD_GPIO_DATA_PORT           GPIOA
#define     LCD_GPIO_D0_PIN              PIN0
#define     LCD_GPIO_D1_PIN              PIN1
#define     LCD_GPIO_D2_PIN              PIN2
#define     LCD_GPIO_D3_PIN              PIN3
#define     LCD_GPIO_D4_PIN              PIN4
#define     LCD_GPIO_D5_PIN              PIN5
#define     LCD_GPIO_D6_PIN              PIN6
#define     LCD_GPIO_D7_PIN              PIN7

#define     LCD_GPIO_CTRL_PORT           GPIOA
#define     LCD_GPIO_EN_PIN              PIN10
#define     LCD_GPIO_RW_PIN              PIN9
#define     LCD_GPIO_RS_PIN              PIN8

#define     LCD_ROWS_NUM                  2

#define     LCD_MAX_DATA_BUFFER_LEN       32

#define     LCD_FIRST_ROW                 0x80
#define     LCD_SCND_ROW                  0xC0

#endif
