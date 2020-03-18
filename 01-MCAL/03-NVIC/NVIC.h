/********************************************************************************************/
/*									AUTHOR  : MIRA MOUSA	                                  								*/
/*									DATE    : MAR 10,2020                 	        			    		    			*/
/*									version : V2.0		  					      	                	    		        */
/********************************************************************************************/

#ifndef NVIC_H_
#define NVIC_H_
/*	
 *	Description :	This section is The Declaration of the APIs 
 *	used in this Drive
 */
 
 
 /*
  * Description   : This API shall Enable a specific interrupt
  * -> Parameters : Copy_u8IntNum (the interrupt number in vector table)
  * -> Return     : ERROR_S 
  *                         ERROR_OK 
  *                         ERROR_NOK
  */
 extern ERROR_S NVIC_EnableInterrupt(u8 Copy_u8IntNum);
 
 
 /*
  * Description   : This API shall Disable a specific interrupt
  * -> Parameters : Copy_u8IntNum (the interrupt number in vector table)
  * -> Return     : ERROR_S 
  *                         ERROR_OK 
  *                         ERROR_NOK
  */
 extern ERROR_S NVIC_DisableInterrupt(u8 Copy_u8IntNum);
 
 /*
  * Description   : This API shall set interrupt's pending flag
  * -> Parameters : Copy_u8IntNum (the interrupt number in vector table)
  * -> Return     : ERROR_S 
  *                         ERROR_OK 
  *                         ERROR_NOK
  */
 extern ERROR_S NVIC_SetPendingFlag(u8 Copy_u8IntNum);

 /*
  * Description   : This API shall clear interrupt's pending flag
  * -> Parameters : Copy_u8IntNum (the interrupt number in vector table)
  * -> Return     : ERROR_S 
  *                         ERROR_OK 
  *                         ERROR_NOK
  */
 extern ERROR_S NVIC_ClearPendingFlag(u8 Copy_u8IntNum);
 
 /*
  * Description   : This API shall set interrupt priority level
  * -> Parameters : Copy_u8GrpSubMask
  * -> Return     : ERROR_S 
  *                         ERROR_OK 
  *                         ERROR_NOK
  */
 extern ERROR_S NVIC_SetPriGROUP(u8 Copy_u8GrpSubMask);
 
 /*
  * Description   : This API shall get interrupt priority level
  * -> Parameters : Copy_u8GrpSubMask
  * -> Return     : ERROR_S 
  *                         ERROR_OK 
  *                         ERROR_NOK
  */
 extern ERROR_S NVIC_GetPriGROUP(u8 *Copy_u8GrpSubMask);
 
 /*
  * Description   : This API shall set interrupt priority level
  * -> Parameters : Copy_u8IntNum (the interrupt number in vector table)
  *                 Copy_u8Priority
  * -> Return     : ERROR_S 
  *                         ERROR_OK 
  *                         ERROR_NOK
  */
 extern ERROR_S NVIC_SetPriorityLevel(u8 Copy_u8IntNum, u8 Copy_u8GroupPriority, u8 Copy_u8SubPriority);
 
 /*
  * Description   : This API shall get interrupt priority level
  * -> Parameters : Copy_u8IntNum (the interrupt number in vector table)
  *                 Copy_u8Priority
  * -> Return     : ERROR_S 
  *                         ERROR_OK 
  *                         ERROR_NOK
  */
 extern ERROR_S NVIC_GetPriorityLevel(u8 Copy_u8IntNum, u8 *Copy_u8Priority);

 /*
  * Description   : This API shall get interrupt active flag
  * -> Parameters : Copy_u8IntNum (the interrupt number in vector table)
  *                 *Copy_u8ActiveFlag 
  * -> Return     : ERROR_S 
  *                         ERROR_OK 
  *                         ERROR_NOK
  */ 
 extern ERROR_S NVIC_GetActiveStatus(u8 Copy_u8IntNum, u8 *Copy_u8ActiveFlag);
 
 /*
  * Description   : This API shall disable all exceptions except NMI and HARD Fault
  * -> Parameters : void
  * -> Return     : ERROR_S 
  *                         ERROR_OK 
  *                         ERROR_NOK
  */ 
 extern ERROR_S NVIC_DisableExternalExceptions(void);
 
 /*
  * Description   : This API shall enable all exceptions except NMI and HARD Fault
  * -> Parameters : void
  * -> Return     : ERROR_S 
  *                         ERROR_OK 
  *                         ERROR_NOK
  */ 
 extern ERROR_S NVIC_EnableExternalExceptions(void);
 
 /*
  * Description   : This API shall disable all exceptions even HARD Fault except NMI 
  * -> Parameters : void
  * -> Return     : ERROR_S 
  *                         ERROR_OK 
  *                         ERROR_NOK
  */ 
 extern ERROR_S NVIC_DisableAllExceptions(void);
 
 /*
  * Description   : This API shall enable all exceptions even HARD Fault except NMI 
  * -> Parameters : void
  * -> Return     : ERROR_S 
  *                         ERROR_OK 
  *                         ERROR_NOK
  */ 
 extern ERROR_S NVIC_EnableAllExceptions(void);
 
 /*
  * Description   : This API shall disable interrupt only with priority lower than Base Priority
  * -> Parameters : Copy_u32BasePriority
  * -> Return     : ERROR_S 
  *                         ERROR_OK 
  *                         ERROR_NOK
  */ 
 extern ERROR_S NVIC_SetBasePriority(u32 Copy_u32BasePriority);
 
 /*
   * Description   : This API shall get Base Priority
   * -> Parameters : *Copy_u32BasePriority
   * -> Return     : ERROR_S
   *                         ERROR_OK
   *                         ERROR_NOK
   */
  extern ERROR_S NVIC_GetBasePriority(u32 *Copy_u32BasePriority);

 
 /*  Groups and subgroups number  */

#define     NVIC_STM_GROUP_SUBGROUP_MASK  	0x00000700
#define		NVIC_GROUPS_16_SUBGROUPS_0   	0x00000300
#define		NVIC_GROUPS_8_SUBGROUPS_2   	0x00000400
#define		NVIC_GROUPS_4_SUBGROUPS_4   	0x00000500
#define		NVIC_GROUPS_2_SUBGROUPS_8   	0x00000600
#define		NVIC_GROUPS_0_SUBGROUPS_16   	0x00000700
 
 /*   Vector table connectivity line devices   */
 
 #define WWDG                     (u8)0
 #define PVD                      (u8)1
 #define TAMPER                   (u8)2
 #define RTC                      (u8)3
 #define FLASH                    (u8)4
 #define RCC                      (u8)5
 #define EXTI0                    (u8)6
 #define EXTI1                    (u8)7
 #define EXTI2                    (u8)8
 #define EXTI3                    (u8)9
 #define EXTI4                    (u8)10
 #define DMA1_Channel1            (u8)11
 #define DMA1_Channel2            (u8)12
 #define DMA1_Channel3            (u8)13
 #define DMA1_Channel4            (u8)14
 #define DMA1_Channel5            (u8)15
 #define DMA1_Channel6            (u8)16
 #define DMA1_Channel7            (u8)17
 #define ADC1_2                   (u8)18
 #define CAN1_TX                  (u8)19
 #define CAN1_RX0                 (u8)20
 #define CAN1_RX1                 (u8)21
 #define CAN1_SCE                 (u8)22
 #define EXTI9_5                  (u8)23
 #define TIM1_BRK                 (u8)24
 #define TIM1_UP                  (u8)25
 #define TIM1_TRG_COM             (u8)26
 #define TIM1_CC                  (u8)27
 #define TIM2                     (u8)28
 #define TIM3                     (u8)29
 #define TIM4                     (u8)30
 #define I2C1_EV                  (u8)31
 #define I2C1_ER                  (u8)32
 #define I2C2_EV                  (u8)33
 #define I2C2_ER                  (u8)34
 #define SPI1                     (u8)35
 #define SPI2                     (u8)36
 #define USART1                   (u8)37
 #define USART2                   (u8)38
 #define USART3                   (u8)39
 #define EXTI15_10                (u8)40
 #define RTCAlarm                 (u8)41
 #define OTG_FS_WKUP              (u8)42
 #define TIM5                     (u8)50
 #define SPI3                     (u8)51
 #define UART4                    (u8)52
 #define UART5                    (u8)53
 #define TIM6                     (u8)54
 #define TIM7                     (u8)55
 #define DMA2_Channel1            (u8)56
 #define DMA2_Channel2            (u8)57
 #define DMA2_Channel3            (u8)58
 #define DMA2_Channel4_5          (u8)59
 
 
 
 
 
#endif 
