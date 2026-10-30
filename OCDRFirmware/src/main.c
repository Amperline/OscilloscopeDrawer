#include "Error_Handler.h"
#include "TIM/TIM3.h"
#include "Touch/Touch.h"
#include "comm/spi.h"
#include "general/tasks.h"
#include "projdefs.h"
#include "stm32f401xc.h"
#include "stm32f4xx_hal.h"
#include "stm32f4xx_hal_cortex.h"
#include "stm32f4xx_hal_gpio.h"
#include "stm32f4xx_hal_gpio_ex.h"
#include "stm32f4xx_hal_i2c.h"
#include "stm32f4xx_hal_rcc.h"
#include "def.h"
#include "FreeRTOS.h"
#include "stm32f4xx_hal_def.h"
#include "stm32f4xx_hal_tim.h"
#include "task.h"
#include "TIM/TIM5.h"
#include "comm/i2c.h"
#include <stdint.h>
#include <sys/_types.h>
#include "general/dotsEv.h"
#include "LCD/lcd_driver.h"
#include "general/touchM.h"
#include "general/DAC.h"

#include "general/menu.h"
void SystemClock_Config(void);
void GPIO_Init(void);
void Values_Init(void);

const u_int16_t time_per_div[2] = {
    1,
    10
};

void setVoltageBack()
{
    while(1)
    {
        setVoltage(0);
        vTaskDelay(pdMS_TO_TICKS(1));
    }
}

osMutexDef(spiMutex);
osMutexDef(dotsMutex);
osMutexDef(syncMutex);

int main(void) {
    HAL_Init();

    //System clock config
    SystemClock_Config();
    //init array of pwm OCR values for sin
    Generate_Sine_LUT();
    //init remaining pins
    GPIO_Init();


    HAL_NVIC_SetPriority(EXTI15_10_IRQn, 5, 0); 
    HAL_NVIC_EnableIRQ(EXTI15_10_IRQn);


    HAL_NVIC_SetPriority(EXTI3_IRQn, 5, 0);
    HAL_NVIC_EnableIRQ(EXTI3_IRQn);

    SPI_Init();

    HAL_Delay(100);
    //Resp for alternating PWM for sin
    TIM5_Init();
    //resp for DAC
    TIM3_Init();

    lcd_init();
    setRotation(1);
    tp_init();

    lcd_clear_screen(0xFFFF); // Білий фон
    uint8_t msg1[] = {"WAITING FOR TOUCH..."};
    lcd_display_string(40, 100, msg1, 16, 0x0000); // Чорний текст
    draw_Menu();

    // for(uint16_t i = 0; i < H_dots; i++)
    // {
        
    //     for(uint16_t j = 0; j < V_dots; j++)
    //     {
    //         ImageArr[i][j] = 1;
    //     }
    // }
    // dots_are_evaluated = 0;

    //tp_adjust();
    HAL_TIM_PWM_Start(&htim5, TIM_CHANNEL_1);
    HAL_NVIC_SetPriority(TIM5_IRQn, 0, 0);
    //Enable interrupt in core
    HAL_NVIC_EnableIRQ(TIM5_IRQn);
    //Enable interrupt
    __HAL_TIM_ENABLE_IT(&htim5, TIM_IT_UPDATE);

    HAL_NVIC_SetPriority(TIM3_IRQn, 6, 0);
    //Enable interrupt in core
    HAL_NVIC_EnableIRQ(TIM3_IRQn);
    //Enable interrupt
    __HAL_TIM_ENABLE_IT(&htim3, TIM_IT_UPDATE);
    HAL_TIM_Base_Start_IT(&htim3);

    spiMutexHandle = osMutexCreate(osMutex(spiMutex));
    dotsArrMutexHandle = osMutexCreate(osMutex(dotsMutex));
    syncMutexHandle = osMutexCreate(osMutex(syncMutex));

    //xTaskCreate(setVoltageBack, "Voltage to 0", 256, NULL, 2, NULL);
    xTaskCreate(checkOnSync, "Check on  sync", 128, NULL, 2, NULL);
    xTaskCreate(checkDotsEvaluation, "Dots evaluation", 256, NULL, 2, NULL);
    xTaskCreate(checkOnTouch, "Touch check", 512, NULL, 3, NULL);
    xTaskCreate(c_DrawPoint, "Touch draw", 512, NULL, 4, NULL);
    xTaskCreate(dacPerform, "DAC Update", 512, NULL, 10, &dacTaskHandle);
    vTaskStartScheduler();

    Error_Handler();

}

void SystemClock_Config(void) {
    __HAL_RCC_PWR_CLK_ENABLE();
    __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE2);

    RCC_OscInitTypeDef RCC_OscInitStruct = {0};
    RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

    // =========================================================================
    // ВАРІАНТ 1: Робота від внутрішнього генератора HSI (16 МГц) -> PLL 84 МГц
    // =========================================================================
    RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
    RCC_OscInitStruct.HSIState = RCC_HSI_ON;
    RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
    
    RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
    RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
    // HSI = 16 МГц. 
    // 16 / 16 (PLLM) = 1 МГц. 
    // 1 * 336 (PLLN) = 336 МГц. 
    // 336 / 4 (PLLP) = 84 МГц для SYSCLK
    RCC_OscInitStruct.PLL.PLLM = 16; 
    RCC_OscInitStruct.PLL.PLLN = 336;
    RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV4;
    RCC_OscInitStruct.PLL.PLLQ = 7;

    // =========================================================================
    // ВАРІАНТ 2 (ЗАКОМЕНТОВАНИЙ): Робота від зовнішнього кварцу HSE (наприклад, 8 МГц)
    // =========================================================================
    /*

    RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
    RCC_OscInitStruct.HSEState = RCC_HSE_ON;
    
    RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
    RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
    // HSE = 8 МГц. 
    // 8 / 8 (PLLM) = 1 МГц. 1 * 336 = 336. 336 / 4 = 84 МГц.
    RCC_OscInitStruct.PLL.PLLM = 8; 
    RCC_OscInitStruct.PLL.PLLN = 336;
    RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV4;
    RCC_OscInitStruct.PLL.PLLQ = 7;
    */
    // =========================================================================

    // Застосовуємо налаштування осцилятора
    if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK) {
        while(1); // Зависаємо тут, якщо помилка (краще, ніж мовчазний збій)
    }

    // Налаштовуємо шини та тактування периферії
    RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK
                                | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
    RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
    RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
    RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
    RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

    // Для 84 МГц потрібна затримка флеш-пам'яті у 2 такти (FLASH_LATENCY_2)
    if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK) {
        while(1);
    }
}

void GPIO_Init(void) {
    // 1. Обов'язково вмикаємо тактування для ВСІХ використовуваних портів
    __HAL_RCC_GPIOD_CLK_ENABLE();
    __HAL_RCC_GPIOA_CLK_ENABLE();
    __HAL_RCC_GPIOC_CLK_ENABLE();
    __HAL_RCC_GPIOB_CLK_ENABLE();
    __HAL_RCC_SPI1_CLK_ENABLE();


    // ========================================
    // PORT B
    // ========================================



    // ========================================
    // PORT A
    // ========================================
    GPIO_InitTypeDef GPIO_InitStruct = {0};
    // PWM (PA0)
    GPIO_InitStruct.Pin = _PWM_PIN;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF2_TIM5;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);


    // USART1 піни (TX, RX) — USART1 це AF7
    GPIO_InitStruct.Pin = _TX_PIN | _RX_PIN;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF7_USART1; 
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
    
    // Front Sync IRQ
    GPIO_InitStruct.Pin = _FRONT_SYNC_IRQ_PIN;
    GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
    GPIO_InitStruct.Pull = GPIO_PULLDOWN;
    HAL_GPIO_Init(_FRONT_SYNC_IRQ_Port, &GPIO_InitStruct);

    // SPI1 піни (SCLK, MISO, MOSI)
    GPIO_InitStruct.Pin = _SCLK_PIN | _MISO_PIN | _MOSI_PIN;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF5_SPI1;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);


    /*Configure GPIO pin Output Level */
    HAL_GPIO_WritePin(LCD_DC_GPIO_Port, LCD_DC_Pin, GPIO_PIN_SET);
    /*Configure GPIO pin Output Level */
    HAL_GPIO_WritePin(GPIOB, SD_CS_Pin|XPT2046_CS_Pin|LCD_CS_Pin, GPIO_PIN_SET);


    /*Configure GPIO pin : PtPin */
    GPIO_InitStruct.Pin = LCD_DC_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_MEDIUM;
    HAL_GPIO_Init(LCD_DC_GPIO_Port, &GPIO_InitStruct);

    /*Configure GPIO pin : PtPin */
    GPIO_InitStruct.Pin = XPT2046_IRQ_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    HAL_GPIO_Init(XPT2046_IRQ_GPIO_Port, &GPIO_InitStruct);

    /*Configure GPIO pins : PBPin PBPin PBPin */
    GPIO_InitStruct.Pin = SD_CS_Pin|XPT2046_CS_Pin|LCD_CS_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_MEDIUM;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = GPIO_PIN_6 | GPIO_PIN_7;
    GPIO_InitStruct.Mode = GPIO_MODE_ANALOG; 
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
}