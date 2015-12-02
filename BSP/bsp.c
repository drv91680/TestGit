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
* Filename      : bsp.c
* Version       : V1.00
* Programmer(s) : BAN
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*                                             INCLUDE FILES
*********************************************************************************************************
*/

#define  _BSP_C_
#include "includes.h"






/*
*********************************************************************************************************
*                                               BSP_Init()
*
* Description : Initialize the Board Support Package (BSP).
*
* Argument(s) : none.
*
* Return(s)   : none.
*
* Caller(s)   : Application.
*
* Note(s)     : (1) This function SHOULD be called before any other BSP function is called.
*********************************************************************************************************
*/

void  BSP_Init (void)
{
    //³õÊ¼»¯ÏµÍ³Ê±ÖÓ72MHZ
    //SystemInit(); //ÒÑÔÚÆô¶¯´úÂëÖÐµ÷ÓÃ
	
	
	//Ê¹ÄÜ¸÷¸öÄ£¿éÊ±ÖÓ
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1
                         |RCC_AHBPeriph_FSMC, 
                         ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO 
                          |RCC_APB2Periph_GPIOA 
                          |RCC_APB2Periph_GPIOB 
                          |RCC_APB2Periph_GPIOC 
                          |RCC_APB2Periph_GPIOD
                          |RCC_APB2Periph_GPIOE 
                          //|RCC_APB2Periph_GPIOF 
                          //|RCC_APB2Periph_GPIOG
                          |RCC_APB2Periph_ADC1   
                          |RCC_APB2Periph_USART1 
                          |RCC_APB2Periph_SPI1  
                          |RCC_APB2Periph_TIM1,
                          //|RCC_APB2Periph_TIM8
                          //|RCC_APB2Periph_ADC2  
                          //|RCC_APB2Periph_ADC3  
                          ENABLE);
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2
                          |RCC_APB1Periph_TIM3
                          //|RCC_APB1Periph_TIM4
                          //|RCC_APB1Periph_TIM5
                          //|RCC_APB1Periph_TIM6
                          //|RCC_APB1Periph_TIM7
                          |RCC_APB1Periph_USART2
                          |RCC_APB1Periph_USART3
                          //|RCC_APB1Periph_UART4
                          //|RCC_APB1Periph_UART5
                          |RCC_APB1Periph_SPI2
                          |RCC_APB1Periph_USB,
                          //|RCC_APB1Periph_SPI3
                          //|RCC_APB1Periph_I2C1
                          //|RCC_APB1Periph_I2C2                          
                          //|RCC_APB1Periph_CAN1                          
                          //|RCC_APB1Periph_WWDG
                          //|RCC_APB1Periph_BKP
                          //|RCC_APB1Periph_PWR
                          //|RCC_APB1Periph_DAC
                          ENABLE);  

	//ÖÐ¶ÏÏòÁ¿±í³õÊ¼»¯
#ifdef  VECT_TAB_RAM
  	/* Set the Vector Table base location at 0x20000000 */
  	NVIC_SetVectorTable(NVIC_VectTab_RAM, 0x0);
#else  /* VECT_TAB_FLASH  */
  	/* Set the Vector Table base location at 0x08000000 */
  	NVIC_SetVectorTable(NVIC_VectTab_FLASH, 0x0);
#endif

	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);

	//ÖÐ¶Ï·þÎñ³ÌÐò³õÊ¼»¯
	BSP_IntInit();
	
  	//³õÊ¼»¯ÍâÉ
	/* Initialize the I/Os for the ADC      controls. */
    //BSP_ADC_Init(); 
    /* Initialize the I/Os for the LED      controls.  */
    BSP_LED_Init();
	KEY_GPIO_Cfg();                                     
    /* Initialize the I/Os for the Joystick control.        */
	//BSP_Joystick_Init(); 

    //STM3210E_LCD_Init();
    //LCD_Clear(0xFFFF);
	LCD_GPIO_Init();
	LCD_CfgInit();
	
	CommGPIOCfg(COMM1);
	CommGPIOCfg(COMM2);
	CommNVICCfg(COMM1);
	CommNVICCfg(COMM2);
	CommCfg(COMM1);
	CommCfg(COMM2);
	
}


/*
*********************************************************************************************************
*                                              BSP_IntInit()
*
* Description : Initialize interrupts:
*
* Argument(s) : none.
*
* Return(s)   : none.
*
* Caller(s)   : BSP_Init().
*
* Note(s)     : none.
*********************************************************************************************************
*/

void  BSP_IntInit(void)
{
    //BSP_IntVectSet(BSP_INT_ID_USART1, USART1_ISR);
    BSP_IntVectSet(BSP_INT_ID_USART2, USART2_ISR);
    //BSP_IntVectSet(BSP_INT_ID_USART2, CommISR(2));
}



/*
*********************************************************************************************************
*                                            BSP_CPU_ClkFreq()
*
* Description : Read CPU registers to determine the CPU clock frequency of the chip.
*
* Argument(s) : none.
*
* Return(s)   : The CPU clock frequency, in Hz.
*
* Caller(s)   : Application.
*
* Note(s)     : none.
*********************************************************************************************************
*/

CPU_INT32U  BSP_CPU_ClkFreq (void)
{
    RCC_ClocksTypeDef  rcc_clocks;


    RCC_GetClocksFreq(&rcc_clocks);

    return ((CPU_INT32U)rcc_clocks.HCLK_Frequency);
}

/*
*********************************************************************************************************
*********************************************************************************************************
*                                         OS CORTEX-M3 FUNCTIONS
*********************************************************************************************************
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*                                         OS_CPU_SysTickClkFreq()
*
* Description : Get system tick clock frequency.
*
* Argument(s) : none.
*
* Return(s)   : Clock frequency (of system tick).
*
* Caller(s)   : BSP_Init().
*
* Note(s)     : none.
*********************************************************************************************************
*/

INT32U  OS_CPU_SysTickClkFreq (void)
{
    INT32U  freq;


    freq = BSP_CPU_ClkFreq();
    return (freq);
}


/*
*********************************************************************************************************
*********************************************************************************************************
*                                              ADC FUNCTIONS
*********************************************************************************************************
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*                                             BSP_ADC_Init()
*
* Description : Initialize the board's ADC,ADC1,ADC_Channel_14,GPIOC
*
* Argument(s) : none.
*
* Return(s)   : none.
*
* Caller(s)   : BSP_Init().
*
* Note(s)     : none.
*********************************************************************************************************
*/

static  void  BSP_ADC_Init (void)
{
    ADC_InitTypeDef   adc_init;
    GPIO_InitTypeDef  gpio_init;

    gpio_init.GPIO_Pin  = GPIO_Pin_4;
    gpio_init.GPIO_Mode = GPIO_Mode_AIN;
    GPIO_Init(GPIOC, &gpio_init);

    adc_init.ADC_Mode               = ADC_Mode_Independent;
    adc_init.ADC_ScanConvMode       = DISABLE;
    adc_init.ADC_ContinuousConvMode = ENABLE;
    adc_init.ADC_ExternalTrigConv   = ADC_ExternalTrigConv_None;
    adc_init.ADC_DataAlign          = ADC_DataAlign_Right;
    adc_init.ADC_NbrOfChannel       = 1;
    ADC_Init(ADC1, &adc_init);

    ADC_RegularChannelConfig(ADC1, ADC_Channel_14, 1, ADC_SampleTime_13Cycles5);
    ADC_Cmd(ADC1, ENABLE);
    ADC_SoftwareStartConvCmd(ADC1, ENABLE);
}


/*
*********************************************************************************************************
*                                           BSP_ADC_GetStatus()
*
* Description : This function initializes the board's ADC
*
* Argument(s) : adc             ID of the ADC to probe.  For this board, the only legitimate value is 1.
*
* Return(s)   : The numerator of the binary fraction representing the result of the latest ADC conversion.
*               This value will be a 12-bit value between 0x0000 and 0x0FFF, inclusive.
*
* Caller(s)   : Application.
*
* Note(s)     : none.
*********************************************************************************************************
*/

CPU_INT16U  BSP_ADC_GetStatus (CPU_INT08U  adc)
{
    CPU_INT16U  result;


    result = 0;

    if (adc == 1) {
        result = ADC_GetConversionValue(ADC1);
    }

    return (result);
}



/*
*********************************************************************************************************
*                                           BSP_PB_GetStatus()
*
* Description : Get the status of a push button on the board.
*
* Argument(s) : pb      The ID of the push button to probe
*
*                       1    probe the user push button
*
* Return(s)   : DEF_FALSE   if the push button is pressed.
*               DEF_TRUE    if the push button is not pressed.
*
* Caller(s)   : Application.
*
* Note(s)     : none.
*********************************************************************************************************
*/

CPU_BOOLEAN  BSP_PB_GetStatus (CPU_INT08U pb)
{
    CPU_BOOLEAN  status;
    CPU_INT32U   pin;


    status = DEF_FALSE;

    switch (pb)
	{
        case BSP_PB_ID_KEY:
             pin = GPIO_ReadInputDataBit(GPIOG, BSP_GPIOG_PB_KEY);
             if (pin == 0) 
			 {
                 status = DEF_TRUE;
             }
             break;

        case BSP_PB_ID_WAKEUP:
             pin = GPIO_ReadInputDataBit(GPIOA, BSP_GPIOA_PB_WAKEUP);
             if (pin == 0) 
			 {
                 status = DEF_TRUE;
             }
             break;

        case BSP_PB_ID_TAMPER:
             pin = GPIO_ReadInputDataBit(GPIOC, BSP_GPIOC_PB_TAMPER);
             if (pin == 0) 
			 {
                 status = DEF_TRUE;
             }
             break;

        default:
             break;
    }

    return (status);
}

/*
*********************************************************************************************************
*********************************************************************************************************
*                                           JOYSTICK FUNCTIONS
*********************************************************************************************************
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*                                           BSP_Joystick_Init()
*
* Description : Initialize the board's joystick.
*
* Argument(s) : none.
*
* Return(s)   : none.
*
* Caller(s)   : BSP_Init().
*
* Note(s)     : none.
*********************************************************************************************************
*/

static  void  BSP_Joystick_Init (void)
{
    GPIO_InitTypeDef  gpio_init;

    /* Configure JOY_UP, JOY_SEL, JOY_LEFT, JOY_RIGHT       */
    gpio_init.GPIO_Pin  = BSP_GPIOG_JOY_UP | BSP_GPIOG_JOY_SEL | BSP_GPIOG_JOY_LEFT | BSP_GPIOG_JOY_RIGHT;
    gpio_init.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(GPIOG, &gpio_init);

    /* Configure JOY_DOWN.                                  */
    gpio_init.GPIO_Pin  = BSP_GPIOD_JOY_DOWN;
    gpio_init.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(GPIOD, &gpio_init);
}

/*
*********************************************************************************************************
*                                        BSP_Joystick_GetStatus()
*
* Description : Get the status of the joystick on the board.
*
* Argument(s) : none.
*
* Return(s)   : Bit-mapped status of joystick :
*
*                   BSP_JOYSTICK_CENTER     if the joystick is being pressed.
*                   BSP_JOYSTICK_LEFT       if the joystick is toggled left.
*                   BSP_JOYSTICK_RIGHT      if the joystick is toggled right.
*                   BSP_JOYSTICK_UP         if the joystick is toggled up.
*                   BSP_JOYSTICK_DOWN       if the joystick is toggled down.
*
* Caller(s)   : Application.
*
* Note(s)     : none.
*********************************************************************************************************
*/

CPU_INT32U  BSP_Joystick_GetStatus (void)
{
    CPU_BOOLEAN  pin;
    CPU_BOOLEAN  status;

    status = 0;

    pin    = GPIO_ReadInputDataBit(GPIOG, BSP_GPIOG_JOY_RIGHT);
    if (pin == 0) {
        status |= BSP_JOYSTICK_LEFT;
    }

    pin    = GPIO_ReadInputDataBit(GPIOG, BSP_GPIOG_JOY_LEFT);
    if (pin == 0) {
        status |= BSP_JOYSTICK_RIGHT;
    }

    pin    = GPIO_ReadInputDataBit(GPIOG, BSP_GPIOG_JOY_UP);
    if (pin == 0) {
        status |= BSP_JOYSTICK_UP;
    }

    pin    = GPIO_ReadInputDataBit(GPIOD, BSP_GPIOD_JOY_DOWN);
    if (pin == 0) {
        status |= BSP_JOYSTICK_DOWN;
    }

    pin    = GPIO_ReadInputDataBit(GPIOG, BSP_GPIOG_JOY_SEL);
    if (pin == 0) {
        status |= BSP_JOYSTICK_CENTER;
    }

    return (status);
}

/*
*********************************************************************************************************
*********************************************************************************************************
*                                              LED FUNCTIONS
*********************************************************************************************************
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*                                             BSP_LED_Init()
*
* Description : Initialize the I/O for the LEDs(·Ü¶·°æÉÏµÄV6¡¢V7¡¢V8)
*
* Argument(s) : none.
*
* Return(s)   : none.
*
* Caller(s)   : BSP_Init().
*
* Note(s)     : none.
*********************************************************************************************************
*/

static  void  BSP_LED_Init (void)
{
    GPIO_InitTypeDef  gpio_init;
	
    gpio_init.GPIO_Pin   = BSP_GPIO_LED_V6;
	gpio_init.GPIO_Speed = GPIO_Speed_50MHz;
	gpio_init.GPIO_Mode  = GPIO_Mode_Out_PP;
	GPIO_Init(GPIOB, &gpio_init);
	
	gpio_init.GPIO_Pin   = BSP_GPIO_LED_V7 | BSP_GPIO_LED_V8;
    GPIO_Init(GPIOD, &gpio_init);
}

/*
*********************************************************************************************************
*                                             BSP_LED_On()
*
* Description : Turn ON any or all the LEDs on the board.
*
* Argument(s) : led     The ID of the LED to control:
*
*                       0    turn ON all LEDs on the board
*                       1    turn ON LED 1
*                       2    turn ON LED 2
*                       3    turn ON LED 3
*                       4    turn OFF all LEDs on the board
*
* Return(s)   : none.
*
* Caller(s)   : Application.
*
* Note(s)     : none.
*********************************************************************************************************
*/

void  BSP_LED_On (CPU_INT08U led)
{
    switch (led) 
	{
        case 0:
             GPIO_SetBits(GPIOB, BSP_GPIO_LED_V6);
			 GPIO_SetBits(GPIOD, BSP_GPIO_LED_V7 | BSP_GPIO_LED_V8);
             break;

        case 1:
             GPIO_SetBits(GPIOB, BSP_GPIO_LED_V6);
             break;

        case 2:
             GPIO_SetBits(GPIOD, BSP_GPIO_LED_V7);
             break;

        case 3:
             GPIO_SetBits(GPIOD, BSP_GPIO_LED_V8);
             break;

        default:
             break;
    }
}

/*
*********************************************************************************************************
*                                              BSP_LED_Off()
*
* Description : Turn OFF any or all the LEDs on the board.
*
* Argument(s) : led     The ID of the LED to control:
*
*                       0    turn OFF all LEDs on the board
*                       1    turn OFF LED 1
*                       2    turn OFF LED 2
*                       3    turn OFF LED 3
*                       4    turn OFF LED 4
*
* Return(s)   : none.
*
* Caller(s)   : Application.
*
* Note(s)     : none.
*********************************************************************************************************
*/

void  BSP_LED_Off (CPU_INT08U led)
{
    switch (led) 
	{
        case 0:
             GPIO_ResetBits(GPIOB, BSP_GPIO_LED_V6);
			 GPIO_ResetBits(GPIOD, BSP_GPIO_LED_V7 | BSP_GPIO_LED_V8);
             break;

        case 1:
             GPIO_ResetBits(GPIOB, BSP_GPIO_LED_V6);
             break;

        case 2:
             GPIO_ResetBits(GPIOD, BSP_GPIO_LED_V7);
             break;

        case 3:
             GPIO_ResetBits(GPIOD, BSP_GPIO_LED_V8);
             break;

        default:
             break;
    }
}


void  BSP_LED_Toggle (CPU_INT08U led)
{
	
}


/*
*********************************************************************************************************
*********************************************************************************************************
*                                            MEMORY FUNCTIONS
*********************************************************************************************************
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*                                             BSP_NAND_Init()
*
* Description : Initialize FSMC for NAND flash.
*
* Argument(s) : none.
*
* Return(s)   : none.
*
* Caller(s)   : Application.
*
* Note(s)     : none.
*********************************************************************************************************
*/

void  BSP_NAND_Init (void)
{
    GPIO_InitTypeDef                   gpio_init;
    FSMC_NANDInitTypeDef               nand_init;
    FSMC_NAND_PCCARDTimingInitTypeDef  p;


    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD | RCC_APB2Periph_GPIOE 
							| RCC_APB2Periph_GPIOF | RCC_APB2Periph_GPIOG, ENABLE);

    /* ---------------------- CFG GPIO -------------------- */
    /* CLE, ALE, D0..3, NOW, NWE & NCE2 NAND pin cfg.       */
    gpio_init.GPIO_Pin   =  GPIO_Pin_11 | GPIO_Pin_12 | GPIO_Pin_14 
    						| GPIO_Pin_15 |GPIO_Pin_0  | GPIO_Pin_1  
                            | GPIO_Pin_4  | GPIO_Pin_5  | GPIO_Pin_7;
    gpio_init.GPIO_Speed = GPIO_Speed_50MHz;
    gpio_init.GPIO_Mode  = GPIO_Mode_AF_PP;

    GPIO_Init(GPIOD, &gpio_init);

    /* D4..7 NAND pin configuration.                        */
    gpio_init.GPIO_Pin   = GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10;

    GPIO_Init(GPIOE, &gpio_init);


                                                                /* NWAIT NAND pin configuration.                        */
    gpio_init.GPIO_Pin   = GPIO_Pin_6;   							
    gpio_init.GPIO_Speed = GPIO_Speed_50MHz;
    gpio_init.GPIO_Mode  = GPIO_Mode_IPU;

    GPIO_Init(GPIOD, &gpio_init);

                                                                /* INT2 NAND pin configuration.                         */
    gpio_init.GPIO_Pin   = GPIO_Pin_6;   							
    GPIO_Init(GPIOG, &gpio_init);

                                                                /* ---------------------- CFG FSMC -------------------- */
    p.FSMC_SetupTime                          = 0x1;
    p.FSMC_WaitSetupTime                      = 0x3;
    p.FSMC_HoldSetupTime                      = 0x2;
    p.FSMC_HiZSetupTime                       = 0x1;

    nand_init.FSMC_Bank                       = FSMC_Bank2_NAND;
    nand_init.FSMC_Waitfeature                = FSMC_Waitfeature_Enable;
    nand_init.FSMC_MemoryDataWidth            = FSMC_MemoryDataWidth_8b;
    nand_init.FSMC_ECC                        = FSMC_ECC_Enable;
    nand_init.FSMC_ECCPageSize                = FSMC_ECCPageSize_512Bytes;
	//FWL V3.0Ã»ÓÐ´ËÏî
	//nand_init.FSMC_AddressLowMapping          = FSMC_AddressLowMapping_Direct;
    nand_init.FSMC_TCLRSetupTime              = 0x00;
    nand_init.FSMC_TARSetupTime               = 0x00;
    nand_init.FSMC_CommonSpaceTimingStruct    = &p;
    nand_init.FSMC_AttributeSpaceTimingStruct = &p;

    FSMC_NANDInit(&nand_init);

    FSMC_NANDCmd(FSMC_Bank2_NAND, ENABLE); /* FSMC NAND bank cmd test.                             */
}

/*
*********************************************************************************************************
*                                             BSP_NOR_Init()
*
* Description : Initialize FSMC for NOR flash.
*
* Argument(s) : none.
*
* Return(s)   : none.
*
* Caller(s)   : Application.
*
* Note(s)     : none.
*********************************************************************************************************
*/

void  BSP_NOR_Init (void)
{
    GPIO_InitTypeDef               gpio_init;
    FSMC_NORSRAMInitTypeDef        nor_init;
    FSMC_NORSRAMTimingInitTypeDef  p;

	/* ---------------------- CFG GPIO -------------------- */
    /* NOR data lines configuration.                        */
    gpio_init.GPIO_Pin   = GPIO_Pin_0  | GPIO_Pin_1  | GPIO_Pin_8 
    | GPIO_Pin_9 | GPIO_Pin_10 | GPIO_Pin_14 | GPIO_Pin_15;
    gpio_init.GPIO_Mode  = GPIO_Mode_AF_PP;
    gpio_init.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOD, &gpio_init);

    gpio_init.GPIO_Pin   = GPIO_Pin_7  | GPIO_Pin_8  | GPIO_Pin_9  
							| GPIO_Pin_10 | GPIO_Pin_11 |
                           GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
    GPIO_Init(GPIOE, &gpio_init);

    /* NOR address lines configuration.                     */
    gpio_init.GPIO_Pin   = GPIO_Pin_0  | GPIO_Pin_1  
    						| GPIO_Pin_2  | GPIO_Pin_3  | GPIO_Pin_4 |
                           GPIO_Pin_5  | GPIO_Pin_12 
                           | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
    GPIO_Init(GPIOF, &gpio_init);

    gpio_init.GPIO_Pin   = GPIO_Pin_0  | GPIO_Pin_1  | GPIO_Pin_2  
							| GPIO_Pin_3  | GPIO_Pin_4 | GPIO_Pin_5;
    GPIO_Init(GPIOG, &gpio_init);

    gpio_init.GPIO_Pin   = GPIO_Pin_11 | GPIO_Pin_12 | GPIO_Pin_13;
    GPIO_Init(GPIOD, &gpio_init);

    gpio_init.GPIO_Pin   = GPIO_Pin_3  | GPIO_Pin_4  | GPIO_Pin_5  | GPIO_Pin_6;
    GPIO_Init(GPIOE, &gpio_init);

    /* NOE and NWE configuration.                           */
    gpio_init.GPIO_Pin   = GPIO_Pin_4  | GPIO_Pin_5;
    GPIO_Init(GPIOD, &gpio_init);

    /* NE2 configuration.                                   */
    gpio_init.GPIO_Pin   = GPIO_Pin_9;
    GPIO_Init(GPIOG, &gpio_init);

    /* ---------------------- CFG FSMC -------------------- */
    p.FSMC_AddressSetupTime             = 0x05;
    p.FSMC_AddressHoldTime              = 0x00;
    p.FSMC_DataSetupTime                = 0x07;
    p.FSMC_BusTurnAroundDuration        = 0x00;
    p.FSMC_CLKDivision                  = 0x00;
    p.FSMC_DataLatency                  = 0x00;
    p.FSMC_AccessMode                   = FSMC_AccessMode_B;

    nor_init.FSMC_Bank                  = FSMC_Bank1_NORSRAM2;
    nor_init.FSMC_DataAddressMux        = FSMC_DataAddressMux_Disable;
    nor_init.FSMC_MemoryType            = FSMC_MemoryType_NOR;
    nor_init.FSMC_MemoryDataWidth       = FSMC_MemoryDataWidth_16b;
    nor_init.FSMC_BurstAccessMode       = FSMC_BurstAccessMode_Disable;
    nor_init.FSMC_WaitSignalPolarity    = FSMC_WaitSignalPolarity_Low;
    nor_init.FSMC_WrapMode              = FSMC_WrapMode_Disable;
    nor_init.FSMC_WaitSignalActive      = FSMC_WaitSignalActive_BeforeWaitState;
    nor_init.FSMC_WriteOperation        = FSMC_WriteOperation_Enable;
    nor_init.FSMC_WaitSignal            = FSMC_WaitSignal_Disable;
    nor_init.FSMC_ExtendedMode          = FSMC_ExtendedMode_Disable;
    //nor_init.FSMC_AsyncWait             = FSMC_WaitSignal_Disable;//FWL V3.3Ã»ÓÐ´ËÏî
    nor_init.FSMC_WriteBurst            = FSMC_WriteBurst_Disable;
    nor_init.FSMC_ReadWriteTimingStruct = &p;
    nor_init.FSMC_WriteTimingStruct     = &p;

    FSMC_NORSRAMInit(&nor_init);

                                                                /* Enable FSMC Bank1_NOR Bank.                          */
    FSMC_NORSRAMCmd(FSMC_Bank1_NORSRAM2, ENABLE);
}

/*
*********************************************************************************************************
*********************************************************************************************************
*                                           OS PROBE FUNCTIONS
*********************************************************************************************************
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*                                           OSProbe_TmrInit()
*
* Description : Select & initialize a timer for use with the uC/Probe Plug-In for uC/OS-II.
*
* Argument(s) : none.
*
* Return(s)   : none.
*
* Caller(s)   : OSProbe_Init().
*
* Note(s)     : none.
*********************************************************************************************************
*/

#if ((APP_OS_PROBE_EN   == DEF_ENABLED) && \
     (OS_PROBE_HOOKS_EN == 1))
void  OSProbe_TmrInit (void)
{
    TIM_TimeBaseInitTypeDef  tim_init;


    tim_init.TIM_Period        = 0xFFFF;
    tim_init.TIM_Prescaler     = 256;
    tim_init.TIM_ClockDivision = TIM_CKD_DIV4;
    tim_init.TIM_CounterMode   = TIM_CounterMode_Up;

#if (OS_PROBE_TIMER_SEL == 2)
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);

    TIM_TimeBaseInit(TIM2, &tim_init);
    TIM_SetCounter(TIM2, 0);
    TIM_PrescalerConfig(TIM2, 256, TIM_PSCReloadMode_Immediate);
    TIM_Cmd(TIM2, ENABLE);
#elif (OS_PROBE_TIMER_SEL == 3)
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);

    TIM_TimeBaseInit(TIM3, &tim_init);
    TIM_SetCounter(TIM3, 0);
    TIM_PrescalerConfig(TIM3, 256, TIM_PSCReloadMode_Immediate);
    TIM_Cmd(TIM3, ENABLE);
#elif (OS_PROBE_TIMER_SEL == 4)
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);

    TIM_TimeBaseInit(TIM4, &tim_init);
    TIM_SetCounter(TIM4, 0);
    TIM_PrescalerConfig(TIM4, 256, TIM_PSCReloadMode_Immediate);
    TIM_Cmd(TIM4, ENABLE);
#endif
}
#endif

/*
*********************************************************************************************************
*                                            OSProbe_TmrRd()
*
* Description : Read the current counts of a 16-bit free running timer.
*
* Argument(s) : none.
*
* Return(s)   : The 16-bit counts of the timer in a 32-bit variable.
*
* Caller(s)   : OSProbe_TimeGetCycles().
*
* Note(s)     : none.
*********************************************************************************************************
*/

#if ((APP_OS_PROBE_EN   == DEF_ENABLED) && \
     (OS_PROBE_HOOKS_EN == 1))
CPU_INT32U  OSProbe_TmrRd (void)
{
#if (OS_PROBE_TIMER_SEL == 2)

    return ((CPU_INT32U)TIM_GetCounter(TIM2));

#elif (OS_PROBE_TIMER_SEL == 3)

    return ((CPU_INT32U)TIM_GetCounter(TIM3));

#elif (OS_PROBE_TIMER_SEL == 4)

    return ((CPU_INT32U)TIM_GetCounter(TIM4));

#endif
}
#endif
