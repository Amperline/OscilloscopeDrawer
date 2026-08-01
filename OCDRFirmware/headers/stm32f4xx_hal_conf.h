#ifndef __STM32F4xx_HAL_CONF_H
#define __STM32F4xx_HAL_CONF_H

#ifdef __cplusplus
extern "C" {
#endif
// -------------------------
// 1. Підключення HAL-модулів (ті, що тобі потрібні)
#define HAL_MODULE_ENABLED

#define HAL_RCC_MODULE_ENABLED     // Тактування
#define HAL_GPIO_MODULE_ENABLED    // GPIO
#define HAL_CORTEX_MODULE_ENABLED  // Cortex-модуль (NVIC, пріоритети)
#define HAL_SYSCFG_MODULE_ENABLED  // Не обов’язково, але часто для EXTI
#define HAL_FLASH_MODULE_ENABLED
#define HAL_DMA_MODULE_ENABLED  
#define HAL_TIM_MODULE_ENABLED //модуль таймерів 
#define HAL_USART_MODULE_ENABLED  
#define HAL_I2C_MODULE_ENABLED  
#define HAL_SPI_MODULE_ENABLED   
#define HAL_ADC_MODULE_ENABLED 
#define HAL_RTC_MODULE_ENABLED
#define HAL_PWR_MODULE_ENABLED

#define HSE_STARTUP_TIMEOUT  100U    // Таймаут старту HSE (зовнішнього кварцу) в мілісекундах
#define LSE_STARTUP_TIMEOUT  5000U   // Таймаут старту LSE (низькочастотного кварцу)
#define EXTERNAL_CLOCK_VALUE 0U

// -------------------------
// 2. Включення заголовків для модулів (потрібні для компіляції)

#include "stm32f4xx_hal_rcc.h"
#include "stm32f4xx_hal_gpio.h"
#include "stm32f4xx_hal_cortex.h"
#include "stm32f4xx_hal_flash.h"

#include "stm32f4xx_hal_dma.h"
// це апаратний модуль у мікроконтролерах STM32, 
// який дозволяє передавати дані між пам’яттю і
//  периферією без втручання ЦПУ (процесора).
#include "stm32f4xx.h"

#include "stm32f4xx_hal_tim.h"
#include "stm32f4xx_hal_usart.h"
#include "stm32f4xx_hal_i2c.h"
#include "stm32f4xx_hal_spi.h"
#include "stm32f4xx_hal_def.h"
#include "stm32f4xx_hal_adc.h"
#include "stm32f4xx_hal_rtc.h"
#include "stm32f4xx_hal_pwr.h"

// -------------------------
// 3. Значення частот (для `HAL_RCC_Get*` і `HAL_Delay`)
#define HSE_VALUE    ((uint32_t)8000000U)   // Зовнішній кварц
#define HSI_VALUE    ((uint32_t)16000000U)  // Внутрішній генератор
#define LSE_VALUE    ((uint32_t)32768U)     // Для RTC (не критично)
#define LSI_VALUE    ((uint32_t)32000U)     // Внутрішній низькочастотний

// -------------------------
// 4. Налаштування `SysTick` і таймеру затримки
#define  TICK_INT_PRIORITY            ((uint32_t)0U)  // Пріоритет SysTick
#define  USE_RTOS                     0               // Без RTOS
#define  PREFETCH_ENABLE              1
#define  INSTRUCTION_CACHE_ENABLE     1
#define  DATA_CACHE_ENABLE            1

// #define USE_FULL_ASSERT    1U
#define USE_FULL_ASSERT
#include "stm32_assert.h"


#ifdef __cplusplus
}
#endif

#endif /* __STM32F4xx_HAL_CONF_H */
