#include "stm32f401xc.h"
#include "stm32f4xx_hal.h"
#include "stm32f4xx_hal_gpio.h"
#include "stm32f4xx_hal_gpio_ex.h"
#include "stm32f4xx_hal_rcc.h"
#include "def.h"
#include "FreeRTOS.h"
#include "stm32f4xx_hal_def.h"
#include "task.h"
#include "TIM/TIM5.h"


void SystemClock_Config(void);
void GPIO_Init(void);

int main() {
    HAL_Init();
    SystemClock_Config();
    GPIO_Init();



    

    
    while (1) {
        HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_13); // Toggle the LED pin
        HAL_Delay(500); // Delay for 
        // 500 milliseconds                  // 5. Затримка 500 мс
    }
}

void SystemClock_Config(void) {
  //Вмикаємо тактування блоку живлення (PWR)
  //Налаштовуємо масштабування напруги: для стабільної 
  //роботи на певній частоті
    __HAL_RCC_PWR_CLK_ENABLE();
    __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE2);

    RCC_OscInitTypeDef RCC_OscInitStruct;
    RCC_ClkInitTypeDef RCC_ClkInitStruct;
    //Вмикаємо внутрішній генератор HSE
    RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
    RCC_OscInitStruct.HSIState = RCC_HSE_ON;
    //RCC_OscInitStruct.HSICalibrationValue

    // PLLM	  Дільник на вході PLL	    16 (HSI/16 = 1 МГц)
    // PLLN	  Множник для VCO	          336 (1×336 = 336 МГц)
    // PLLP	  Дільник для SYSCLK (CPU)	/4 (336 / 4 = 84 МГц)
    // PLLQ	  Дільник для USB/SDIO/RNG	/7 (336 / 7 = ~48 МГц)

    RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
    RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
    RCC_OscInitStruct.PLL.PLLM = 8;
    RCC_OscInitStruct.PLL.PLLN = 336;
    RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV4;
    RCC_OscInitStruct.PLL.PLLQ = 7;
    HAL_RCC_OscConfig(&RCC_OscInitStruct);

    RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK
                                | RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2;
    RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
    RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
    RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
    RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

    // STM32 флеш-пам'ять має затримку (wait states).
    // Для 84 МГц потрібно FLASH_LATENCY_2 (2 такти).
    HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2);
}

void GPIO_Init(void) {
    // Макрос, який вмикає тактування для порту GPIOC через RCC.
    __HAL_RCC_GPIOB_CLK_ENABLE();
    __HAL_RCC_GPIOA_CLK_ENABLE();

//////////PORT B
    #define _TP_IRQ_PIN GPIO_PIN_12

    GPIO_InitTypeDef gpio_LCD_DC = {0};
    HAL_GPIO_WritePin(GPIOB, _LCD_DC_PIN, GPIO_PIN_RESET);
    gpio_LCD_DC.Pin = _LCD_DC_PIN;
    gpio_LCD_DC.Mode = GPIO_MODE_OUTPUT_PP;
    gpio_LCD_DC.Pull = GPIO_PULLDOWN;
    gpio_LCD_DC.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    gpio_LCD_DC.Alternate = GPIO_AF2_TIM5;
    HAL_GPIO_Init(GPIOB, &gpio_LCD_DC);

    GPIO_InitTypeDef gpio_LCD_CS = {0};
    HAL_GPIO_WritePin(GPIOB, _LCD_CS_PIN, GPIO_PIN_RESET);
    gpio_LCD_CS.Pin = _LCD_DC_PIN;
    gpio_LCD_CS.Mode = GPIO_MODE_OUTPUT_PP;
    gpio_LCD_CS.Pull = GPIO_PULLDOWN;
    gpio_LCD_CS.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    gpio_LCD_CS.Alternate = GPIO_AF2_TIM5;
    HAL_GPIO_Init(GPIOB, &gpio_LCD_CS);

    GPIO_InitTypeDef gpio_TP_CS = {0};
    HAL_GPIO_WritePin(GPIOB, _TP_CS_PIN, GPIO_PIN_RESET);
    gpio_TP_CS.Pin = _TP_CS_PIN;
    gpio_TP_CS.Mode = GPIO_MODE_AF_PP;
    gpio_TP_CS.Pull = GPIO_PULLDOWN;
    gpio_TP_CS.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    gpio_TP_CS.Alternate = GPIO_AF2_TIM5;
    HAL_GPIO_Init(GPIOB, &gpio_TP_CS);

    GPIO_InitTypeDef gpio_SD_CS = {0};
    HAL_GPIO_WritePin(GPIOB, _SD_CS_PIN, GPIO_PIN_RESET);
    gpio_SD_CS.Pin = _SD_CS_PIN;
    gpio_SD_CS.Mode = GPIO_MODE_AF_PP;
    gpio_SD_CS.Pull = GPIO_PULLDOWN;
    gpio_SD_CS.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    gpio_SD_CS.Alternate = GPIO_AF2_TIM5;
    HAL_GPIO_Init(GPIOB, &gpio_SD_CS);

    GPIO_InitTypeDef gpio_SCL = {0};
    HAL_GPIO_WritePin(GPIOB, _SCL_PIN, GPIO_PIN_RESET);
    gpio_SCL.Pin = _SCL_PIN;
    gpio_SCL.Mode = GPIO_MODE_AF_PP;
    gpio_SCL.Pull = GPIO_NOPULL;
    gpio_SCL.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    gpio_SCL.Alternate = GPIO_AF4_I2C1;
    HAL_GPIO_Init(GPIOB, &gpio_SCL);

    GPIO_InitTypeDef gpio_SDA = {0};
    HAL_GPIO_WritePin(GPIOB, _SDA_PIN, GPIO_PIN_RESET);
    gpio_SDA.Pin = _SDA_PIN;
    gpio_SDA.Mode = GPIO_MODE_AF_PP;
    gpio_SDA.Pull = GPIO_NOPULL;
    gpio_SDA.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    gpio_SDA.Alternate = GPIO_AF4_I2C1;
    HAL_GPIO_Init(GPIOB, &gpio_SDA);

    GPIO_InitTypeDef gpio_TP_IRQ = {0};
    HAL_GPIO_WritePin(GPIOB, _TP_IRQ_PIN, GPIO_PIN_RESET);
    gpio_TP_IRQ.Pin = _TP_IRQ_PIN;
    gpio_TP_IRQ.Mode = GPIO_MODE_OUTPUT_PP;
    gpio_TP_IRQ.Pull = GPIO_PULLDOWN;
    gpio_TP_IRQ.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    HAL_GPIO_Init(GPIOB, &gpio_TP_IRQ);

//////////PORT A
    GPIO_InitTypeDef gpioPWM = {0};
    HAL_GPIO_WritePin(GPIOA, _PWM_PIN, GPIO_PIN_RESET);
    gpioPWM.Pin = _PWM_PIN;
    gpioPWM.Mode = GPIO_MODE_AF_PP;
    gpioPWM.Pull = GPIO_PULLDOWN;
    gpioPWM.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    gpioPWM.Alternate = GPIO_AF2_TIM5;
    HAL_GPIO_Init(GPIOA, &gpioPWM);

    GPIO_InitTypeDef gpioSCLK = {0};
    HAL_GPIO_WritePin(GPIOA, _SCLK_PIN, GPIO_PIN_RESET);
    gpioSCLK.Pin = _SCLK_PIN;
    gpioSCLK.Mode = GPIO_MODE_AF_PP;
    gpioSCLK.Pull = GPIO_PULLDOWN;
    gpioSCLK.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    gpioSCLK.Alternate = GPIO_AF5_SPI1;
    HAL_GPIO_Init(GPIOA, &gpioSCLK);

    GPIO_InitTypeDef gpioMISO = {0};
    HAL_GPIO_WritePin(GPIOA, _MISO_PIN, GPIO_PIN_RESET);
    gpioMISO.Pin = _MISO_PIN;
    gpioMISO.Mode = GPIO_MODE_AF_PP;
    gpioMISO.Pull = GPIO_NOPULL;
    gpioMISO.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    gpioMISO.Alternate = GPIO_AF5_SPI1;
    HAL_GPIO_Init(GPIOA, &gpioMISO);

    GPIO_InitTypeDef gpioMOSI = {0};
    HAL_GPIO_WritePin(GPIOA, _MOSI_PIN, GPIO_PIN_RESET);
    gpioMOSI.Pin = _MOSI_PIN;
    gpioMOSI.Mode = GPIO_MODE_AF_PP;
    gpioMOSI.Pull = GPIO_NOPULL;
    gpioMOSI.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    gpioMOSI.Alternate = GPIO_AF5_SPI1;
    HAL_GPIO_Init(GPIOA, &gpioMISO);

    GPIO_InitTypeDef gpioUSART_TX = {0};
    HAL_GPIO_WritePin(GPIOA, _TX_PIN, GPIO_PIN_RESET);
    gpioUSART_TX.Pin = _TX_PIN;
    gpioUSART_TX.Mode = GPIO_MODE_AF_PP;
    gpioUSART_TX.Pull = GPIO_NOPULL;
    gpioUSART_TX.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    gpioUSART_TX.Alternate = GPIO_AF5_SPI1;
    HAL_GPIO_Init(GPIOA, &gpioUSART_TX);

    GPIO_InitTypeDef gpioUSART_RX = {0};
    HAL_GPIO_WritePin(GPIOA, _RX_PIN, GPIO_PIN_RESET);
    gpioUSART_RX.Pin = _RX_PIN;
    gpioUSART_RX.Mode = GPIO_MODE_AF_PP;
    gpioUSART_RX.Pull = GPIO_NOPULL;
    gpioUSART_RX.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    gpioUSART_RX.Alternate = GPIO_AF5_SPI1;
    HAL_GPIO_Init(GPIOA, &gpioUSART_RX);
    
    GPIO_InitTypeDef gpioFRONT_SYNC = {0};
    HAL_GPIO_WritePin(GPIOA, _FRONT_SYNC_IRQ_PIN, GPIO_PIN_RESET);
    gpioFRONT_SYNC.Pin = _FRONT_SYNC_IRQ_PIN;
    gpioFRONT_SYNC.Mode = GPIO_MODE_INPUT;
    gpioFRONT_SYNC.Pull = GPIO_NOPULL;
    gpioFRONT_SYNC.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    HAL_GPIO_Init(GPIOA, &gpioFRONT_SYNC);



    
}