/**
  ******************************************************************************
  * @file    FreeRTOS/FreeRTOS_ThreadCreation/Src/stm32h7xx_hal_timebase_tim.c
  * @author  MCD Application Team
  * @brief   HAL time base based on the hardware TIM.
  *          This file overrides the native HAL time base functions (defined as weak)
  *          the TIM time base:
  *           + Intializes the TIM peripheral generate a Period elapsed Event each 1ms
  *           + HAL_IncTick is called inside HAL_TIM_PeriodElapsedCallback ie each 1ms
  * 
  ******************************************************************************
 * @attention
  *
  * <h2><center>&copy; Copyright (c) 2019 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "stm32h7xx_hal.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
TIM_HandleTypeDef        TimHandle_TimeBase;
/* Private function prototypes -----------------------------------------------*/
void TIM7_IRQHandler(void);
/* Private functions ---------------------------------------------------------*/

/**
  * @brief  This function configures the TIM6 as a time base source. 
  *         The time source is configured to have 1ms time base with a dedicated 
  *         Tick interrupt priority. 
  * @note   This function is called  automatically at the beginning of program after
  *         reset by HAL_Init() or at any time when clock is configured, by HAL_RCC_ClockConfig(). 
  * @param  TickPriority: Tick interrupt priority.
  * @retval HAL status
  */
HAL_StatusTypeDef HAL_InitTick (uint32_t TickPriority)
{
  RCC_ClkInitTypeDef    clkconfig;
  uint32_t              uwTimclock, uwAPB1Prescaler = 0U;
  uint32_t              uwPrescalerValue = 0U;
  uint32_t              pFLatency;
  
    /*Configure the TIM7 IRQ priority */
  HAL_NVIC_SetPriority(TIM6_DAC_IRQn, TickPriority ,0xFU);
  
  /* Enable the TIM7 global Interrupt */
  HAL_NVIC_EnableIRQ(TIM7_IRQn);
  
  /* Enable TIM7 clock */
  __HAL_RCC_TIM7_CLK_ENABLE();
  
  /* Get clock configuration */
  HAL_RCC_GetClockConfig(&clkconfig, &pFLatency);
  
  /* Get APB1 prescaler */
  uwAPB1Prescaler = clkconfig.APB1CLKDivider;
  
  /* Compute TIM6 clock */
  if (uwAPB1Prescaler == RCC_HCLK_DIV1) 
  {
    uwTimclock = HAL_RCC_GetPCLK1Freq();
  }
  else
  {
    uwTimclock = 2UL * HAL_RCC_GetPCLK1Freq();
  }
  
  /* Compute the prescaler value to have TIM6 counter clock equal to 1MHz */
  uwPrescalerValue = (uint32_t) ((uwTimclock / 1000000U) - 1U);
  
  /* Initialize TIM7 */
  TimHandle_TimeBase.Instance = TIM7;
  
  /* Initialize TIMx peripheral as follow:
  + Period = [(TIM6CLK/1000) - 1]. to have a (1/1000) s time base.
  + Prescaler = (uwTimclock/1000000 - 1) to have a 1MHz counter clock.
  + ClockDivision = 0
  + Counter direction = Up
  */
  TimHandle_TimeBase.Init.Period = (1000000U / 1000U) - 1U;
  TimHandle_TimeBase.Init.Prescaler = uwPrescalerValue;
  TimHandle_TimeBase.Init.ClockDivision = 0;
  TimHandle_TimeBase.Init.CounterMode = TIM_COUNTERMODE_UP;
  if(HAL_TIM_Base_Init(&TimHandle_TimeBase) == HAL_OK)
  {
    /* Start the TIM time Base generation in interrupt mode */
    if(HAL_TIM_Base_Start_IT(&TimHandle_TimeBase) == HAL_OK)
    {
      uwTick = 0;
      return HAL_OK;
    }
  }
  
  /* Return function status */
  return HAL_ERROR;
}

/**
  * @brief  Suspend Tick increment.
  * @note   Disable the tick increment by disabling TIM6 update interrupt.
  * @param  None
  * @retval None
  */
void HAL_SuspendTick(void)
{
  /* Disable TIM6 update Interrupt */
  __HAL_TIM_DISABLE_IT(&TimHandle_TimeBase, TIM_IT_UPDATE);
}

/**
  * @brief  Resume Tick increment.
  * @note   Enable the tick increment by Enabling TIM6 update interrupt.
  * @param  None
  * @retval None
  */
void HAL_ResumeTick(void)
{
  /* Enable TIM6 Update interrupt */
  __HAL_TIM_ENABLE_IT(&TimHandle_TimeBase, TIM_IT_UPDATE);
}

/**
  * @brief  Period elapsed callback in non blocking mode
  * @note   This function is called  when TIM6 interrupt took place, inside
  * HAL_TIM_IRQHandler(). It makes a direct call to HAL_IncTick() to increment
  * a global variable "uwTick" used as application time base.
  * @param  htim : TIM handle
  * @retval None
  */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
  /* Prevent unused argument(s) compilation warning */
  UNUSED(htim);

  HAL_IncTick();
}

/**
  * @brief  This function handles TIM interrupt request.
  * @param  None
  * @retval None
  */
void TIM7_IRQHandler(void)
{
  HAL_TIM_IRQHandler(&TimHandle_TimeBase);
}

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
