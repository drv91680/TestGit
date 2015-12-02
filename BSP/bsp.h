/*
*********************************************************************************************************
*                                     MICIRUM BOARD SUPPORT PACKAGE
*
*                            (c) Copyright 2007-2008; Micrium, Inc.; Weston, FL
*
*                   All rights reserved.  Protected by international copyright laws.
*                   Knowledge of the source code may not be used to write a similar
*                   product.  This file may only be used in accordance with a license
*                   and should not be redistributed in any way.
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*
*                                        BOARD SUPPORT PACKAGE
*
*                                     ST Microelectronics STM32
*                                              with the
*                                   STM3210E-EVAL Evaluation Board
*
* Filename      : bsp.h
* Version       : V1.00
* Programmer(s) : BAN
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*                                                 MODULE
*
* Note(s) : (1) This header file is protected from multiple pre-processor inclusion through use of the
*               BSP present pre-processor macro definition.
*********************************************************************************************************
*/

#ifndef  _BSP_H_
#define  _BSP_H_

/*
*********************************************************************************************************
*                                                 EXTERNS
*********************************************************************************************************
*/

#ifdef   _BSP_C_
#define  BSP_EXT
#else
#define  BSP_EXT  extern
#endif




/*
*********************************************************************************************************
*                                            LOCAL DEFINES
*********************************************************************************************************
*/
                                                                /* -------------------- GPIOA PINS -------------------- */
#define  BSP_GPIOA_PB_WAKEUP                      DEF_BIT_00
#define  BSP_GPIOA_USART2_CTS                     DEF_BIT_00    /* USART2.                                              */
#define  BSP_GPIOA_USART2_RTS                     DEF_BIT_01    /* USART2.                                              */
#define  BSP_GPIOA_USART2_TX                      DEF_BIT_02    /* USART2.                                              */
#define  BSP_GPIOA_USART2_RX                      DEF_BIT_03    /* USART2.                                              */
#define  BSP_GPIOA_LCD_BL                         DEF_BIT_08    /* LCD.                                                 */
#define  BSP_GPIOA_USART1_TX                      DEF_BIT_09    /* USART1.                                              */
#define  BSP_GPIOA_USART1_RX                      DEF_BIT_10    /* USART1.                                              */
#define  BSP_GPIOA_USB_DM                         DEF_BIT_11    /* USB.                                                 */
#define  BSP_GPIOA_USB_DP                         DEF_BIT_12    /* USB.                                                 */

                                                                /* -------------------- GPIOB PINS -------------------- */
#define  BSP_GPIOB_SMARTCARD_PWR_SEL              DEF_BIT_00    /* Smartcard.                                           */
#define  BSP_GPIOB_SMARTCARD_IOUC                 DEF_BIT_10    /* Smartcard.                                           */
#define  BSP_GPIOB_SMARTCARD_RSTIN                DEF_BIT_11    /* Smartcard.                                           */
#define  BSP_GPIOB_SMARTCARD_XTAL1                DEF_BIT_12    /* Smartcard.                                           */
#define  BSP_GPIOB_USB_DISCONNECT                 DEF_BIT_14    /* USB.                                                 */

                                                                /* -------------------- GPIOC PINS -------------------- */
#define  BSP_GPIOC_ANALOG_CN5                     DEF_BIT_01    /* Analog Input.                                        */
#define  BSP_GPIOC_ANALOG_CN3                     DEF_BIT_02    /* Analog Input.                                        */
#define  BSP_GPIOC_ANALOG_CN2                     DEF_BIT_03    /* Analog Input.                                        */
#define  BSP_GPIOC_POT                            DEF_BIT_04    /* Potentiometer.                                       */
#define  BSP_GPIOC_SMARTCARD_CMDVCC               DEF_BIT_06    /* Smartcard.                                           */
#define  BSP_GPIOC_SMARTCARD_OFF                  DEF_BIT_07    /* Smartcard.                                           */
#define  BSP_GPIOC_MICROSD_D0                     DEF_BIT_08    /* MicroSD.                                             */
#define  BSP_GPIOC_MICROSD_D1                     DEF_BIT_09    /* MicroSD.                                             */
#define  BSP_GPIOC_MICROSD_D2                     DEF_BIT_10    /* MicroSD.                                             */
#define  BSP_GPIOC_MICROSD_D3                     DEF_BIT_11    /* MicroSD.                                             */
#define  BSP_GPIOC_MICROSD_CLK                    DEF_BIT_12    /* MicroSD.                                             */
#define  BSP_GPIOC_PB_TAMPER                      DEF_BIT_13

                                                                /* -------------------- GPIOD PINS -------------------- */
#define  BSP_GPIOD_MICROSD_CMD                    DEF_BIT_02    /* MicroSD.                                             */
#define  BSP_GPIOD_JOY_DOWN                       DEF_BIT_03    /* Joystick.                                            */

                                                                /* -------------------- GPIOF PINS -------------------- */
#define  BSP_GPIO_LED_V6                          GPIO_Pin_5    /* LED.                                                 */
#define  BSP_GPIO_LED_V7                          GPIO_Pin_6    /* LED.                                                 */
#define  BSP_GPIO_LED_V8                          GPIO_Pin_3    /* LED.                                                 */
#define  BSP_GPIOF_LED4                           DEF_BIT_09    /* LED.                                                 */
#define  BSP_GPIOA_LCD_CD                         DEF_BIT_10    /* LCD.                                                 */
#define  BSP_GPIOF_MICROSD_DETECT                 DEF_BIT_11    /* MicroSD.                                             */

                                                                /* -------------------- GPIOG PINS -------------------- */
#define  BSP_GPIOG_FSMC_INT2                      DEF_BIT_06    /* FSMC.                                                */
#define  BSP_GPIOG_JOY_SEL                        DEF_BIT_07    /* Joystick.                                            */
#define  BSP_GPIOG_PB_KEY                         DEF_BIT_08    /* Button.                                              */
#define  BSP_GPIOG_FSMC_NE2                       DEF_BIT_09    /* FSMC.                                                */
#define  BSP_GPIOG_FSMC_NE3                       DEF_BIT_10    /* FSMC.                                                */
#define  BSP_GPIOG_AUDIO_PDN                      DEF_BIT_11    /* Audio.                                               */
#define  BSP_GPIOG_FSMC_NE4                       DEF_BIT_12    /* FSMC.                                                */
#define  BSP_GPIOG_JOY_RIGHT                      DEF_BIT_13    /* Joystick.                                            */
#define  BSP_GPIOG_JOY_LEFT                       DEF_BIT_14    /* Joystick.                                            */
#define  BSP_GPIOG_JOY_UP                         DEF_BIT_15    /* Joystick.                                            */


/*
*********************************************************************************************************
*                                                 DEFINES
*********************************************************************************************************
*/

#define  BSP_JOYSTICK_NONE                       DEF_BIT_NONE
#define  BSP_JOYSTICK_UP                         DEF_BIT_00
#define  BSP_JOYSTICK_DOWN                       DEF_BIT_01
#define  BSP_JOYSTICK_LEFT                       DEF_BIT_02
#define  BSP_JOYSTICK_RIGHT                      DEF_BIT_03
#define  BSP_JOYSTICK_CENTER                     DEF_BIT_04

#define  BSP_PB_ID_KEY                                     1
#define  BSP_PB_ID_WAKEUP                                  2
#define  BSP_PB_ID_TAMPER                                  3


/*
*********************************************************************************************************
*                                      LOCAL FUNCTION PROTOTYPES
*********************************************************************************************************
*/

static void  BSP_IntInit(void);

static  void  BSP_ADC_Init     (void);
static  void  BSP_Joystick_Init(void);
static  void  BSP_LED_Init     (void);


/*
*********************************************************************************************************
*                                           FUNCTION PROTOTYPES
*********************************************************************************************************
*/

BSP_EXT void         BSP_Init                    (void);
BSP_EXT CPU_INT32U   BSP_CPU_ClkFreq             (void);

/*
*********************************************************************************************************
*                                              ADC SERVICES
*********************************************************************************************************
*/

BSP_EXT CPU_INT16U   BSP_ADC_GetStatus           (CPU_INT08U     led);

/*
*********************************************************************************************************
*                                           JOYSTICK SERVICES
*********************************************************************************************************
*/

BSP_EXT CPU_INT32U   BSP_Joystick_GetStatus      (void);

/*
*********************************************************************************************************
*                                              LED SERVICES
*********************************************************************************************************
*/

BSP_EXT void         BSP_LED_On                  (CPU_INT08U     led);
BSP_EXT void         BSP_LED_Off                 (CPU_INT08U     led);
BSP_EXT void         BSP_LED_Toggle              (CPU_INT08U     led);

/*
*********************************************************************************************************
*                                               PB SERVICES
*********************************************************************************************************
*/

BSP_EXT CPU_BOOLEAN  BSP_PB_GetStatus            (CPU_INT08U     pb);

/*
*********************************************************************************************************
*                                             MEMORY SERVICES
*********************************************************************************************************
*/

BSP_EXT void         BSP_NAND_Init               (void);
BSP_EXT void         BSP_NOR_Init                (void);



/*
*********************************************************************************************************
*                                               MODULE END
*********************************************************************************************************
*/

#endif                                                          /* End of module include.                               */
