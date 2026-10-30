/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    stm32f4xx_it.c
  * @brief   Interrupt Service Routines.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */


#include "TIM/TIM3.h"
#include "comm/i2c.h"
#include "stm32f401xc.h"
#include "stm32f4xx_hal.h"
#include "def.h"
#include "math.h"
#include "stm32f4xx_hal_gpio.h"
#include "stm32f4xx_hal_tim.h"
#include <stdint.h>
#include <sys/types.h>
/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_it.h"
/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN TD */

/* USER CODE END TD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/* External variables --------------------------------------------------------*/

/* USER CODE BEGIN EV */

/* USER CODE END EV */

/******************************************************************************/
/*           Cortex-M4 Processor Interruption and Exception Handlers          */
/******************************************************************************/
/**
  * @brief This function handles Non maskable interrupt.
  */
void NMI_Handler(void)
{
  /* USER CODE BEGIN NonMaskableInt_IRQn 0 */

  /* USER CODE END NonMaskableInt_IRQn 0 */
  /* USER CODE BEGIN NonMaskableInt_IRQn 1 */
   while (1)
  {
  }
  /* USER CODE END NonMaskableInt_IRQn 1 */
}

/**
  * @brief This function handles Hard fault interrupt.
  */
void HardFault_Handler(void)
{
  /* USER CODE BEGIN HardFault_IRQn 0 */

  /* USER CODE END HardFault_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_HardFault_IRQn 0 */
    /* USER CODE END W1_HardFault_IRQn 0 */
  }
}

/**
  * @brief This function handles Memory management fault.
  */
void MemManage_Handler(void)
{
  /* USER CODE BEGIN MemoryManagement_IRQn 0 */

  /* USER CODE END MemoryManagement_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_MemoryManagement_IRQn 0 */
    /* USER CODE END W1_MemoryManagement_IRQn 0 */
  }
}

/**
  * @brief This function handles Pre-fetch fault, memory access fault.
  */
void BusFault_Handler(void)
{
  /* USER CODE BEGIN BusFault_IRQn 0 */

  /* USER CODE END BusFault_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_BusFault_IRQn 0 */
    /* USER CODE END W1_BusFault_IRQn 0 */
  }
}

/**
  * @brief This function handles Undefined instruction or illegal state.
  */
void UsageFault_Handler(void)
{
  /* USER CODE BEGIN UsageFault_IRQn 0 */

  /* USER CODE END UsageFault_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_UsageFault_IRQn 0 */
    /* USER CODE END W1_UsageFault_IRQn 0 */
  }
}

/**
  * @brief This function handles System service call via SWI instruction.
  */
__attribute__((weak)) void SVC_Handler(void)
{
  /* USER CODE BEGIN SVCall_IRQn 0 */

  /* USER CODE END SVCall_IRQn 0 */
  /* USER CODE BEGIN SVCall_IRQn 1 */

  /* USER CODE END SVCall_IRQn 1 */
}

/**
  * @brief This function handles Debug monitor.
  */
void DebugMon_Handler(void)
{
  /* USER CODE BEGIN DebugMonitor_IRQn 0 */

  /* USER CODE END DebugMonitor_IRQn 0 */
  /* USER CODE BEGIN DebugMonitor_IRQn 1 */

  /* USER CODE END DebugMonitor_IRQn 1 */
}

/**
  * @brief This function handles Pendable request for system service.
  */
__attribute__((weak)) void PendSV_Handler(void)
{
  /* USER CODE BEGIN PendSV_IRQn 0 */

  /* USER CODE END PendSV_IRQn 0 */
  /* USER CODE BEGIN PendSV_IRQn 1 */

  /* USER CODE END PendSV_IRQn 1 */
}

/**
  * @brief This function handles System tick timer.
  */
__attribute__((weak)) void SysTick_Handler(void)
{
  /* USER CODE BEGIN SysTick_IRQn 0 */

  /* USER CODE END SysTick_IRQn 0 */
  HAL_IncTick();
  /* USER CODE BEGIN SysTick_IRQn 1 */

  /* USER CODE END SysTick_IRQn 1 */
}

#include "TIM/TIM5.h"

void TIM5_IRQHandler(void)
{
  // Оновлюємо регістр порівняння значенням з масиву
  __HAL_TIM_SET_COMPARE(&htim5, TIM_CHANNEL_1, sine_arr[lut_index]);
  
  // Рухаємось по масиву
  lut_index++;
  if(lut_index >= 400) 
  {
      lut_index = 0; // Починаємо новий період
  }

  // Очищення прапорів та виклик колбеків HAL
  HAL_TIM_IRQHandler(&htim5);
}



// #include "general/dotsEv.h"

// uint8_t currSection = 0;
// uint16_t currentDot = 0;

// void TIM3_IRQHandler(void)
// {
//   if(currentDot == 0)
//     setVoltage(120);
//   // 1. Одразу очищаємо прапор переривання!
//   __HAL_TIM_CLEAR_IT(&htim3, TIM_IT_UPDATE); 
//   // Або можна використати HAL_TIM_IRQHandler(&htim3);
  
//   while(evaluated_dots[currSection][currentDot] != 255)
//   {
//     setVoltage(evaluated_dots[currSection][currentDot]);
//     currentDot++;
//   }

//   currentDot++;

//   if(evaluated_dots[currSection][currentDot] == 254)
//   {
//     currentDot = 0;
//     currSection ^= 0x01;
//   }

//   setVoltage(0);
//   HAL_TIM_IRQHandler(&htim3);
// }


#include "general/dotsEv.h"
#include "general/DAC.h"

extern TaskHandle_t dacTaskHandle;

void TIM3_IRQHandler(void)
{

  // 1. Очищаємо прапор переривання
  __HAL_TIM_CLEAR_IT(&htim3, TIM_IT_UPDATE); 
  
  // 2. Сповіщаємо задачу DAC, що настав час оновити дані
  BaseType_t xHigherPriorityTaskWoken = pdFALSE;
  vTaskNotifyGiveFromISR(dacTaskHandle, &xHigherPriorityTaskWoken);
  
  // 3. Змушуємо планувальник миттєво переключити контекст, якщо задача DAC має вищий пріоритет
  portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
}




void EXTI15_10_IRQHandler(void)
{
  if (__HAL_GPIO_EXTI_GET_IT(XPT2046_IRQ_Pin) != RESET)
  {
    //clear stm flag
    __HAL_GPIO_EXTI_CLEAR_IT(XPT2046_IRQ_Pin);
    touch_flag = 1; 
  }
  
}

void EXTI3_IRQHandler(void)
{
  sync_flag = 1;
  __HAL_GPIO_EXTI_CLEAR_IT(_FRONT_SYNC_IRQ_PIN);
}

/******************************************************************************/
/* STM32F4xx Peripheral Interrupt Handlers                                    */
/* Add here the Interrupt Handlers for the used peripherals.                  */
/* For the available peripheral interrupt handler names,                      */
/* please refer to the startup file (startup_stm32f4xx.s).                    */
/******************************************************************************/

/* USER CODE BEGIN 1 */

/* USER CODE END 1 */
