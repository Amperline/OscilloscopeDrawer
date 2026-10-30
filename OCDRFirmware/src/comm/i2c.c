#include "comm/i2c.h"
#include "TIM/TIM3.h"
#include "def.h"
#include "stm32f4xx_hal_i2c.h"
#include "Error_Handler.h"
#include "stm32f4xx_hal_usart.h"
#include <stdint.h>

I2C_HandleTypeDef hi2c = {0};

void I2C_Init()
{
    __HAL_RCC_I2C1_CLK_ENABLE();

    __HAL_RCC_I2C1_FORCE_RESET();  // Жорстко скидаємо блок I2C
    HAL_Delay(2);                  // Чекаємо пару мілісекунд
    __HAL_RCC_I2C1_RELEASE_RESET();// Відпускаємо скидання

    hi2c.Instance = I2C1;

    hi2c.Init.ClockSpeed = 400000;
    hi2c.Init.DutyCycle = I2C_DUTYCYCLE_2;
    hi2c.Init.OwnAddress1 = 0;
    hi2c.Init.OwnAddress2 = 0;
    hi2c.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
    hi2c.Init.GeneralCallMode = I2C_GENERALCALL_DISABLED;
    hi2c.Init.DualAddressMode = I2C_DUALADDRESS_DISABLED;
    hi2c.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;

    if (HAL_I2C_Init(&hi2c) != HAL_OK)
    {
        // Якщо сталася помилка, переходимо в обробник помилок (наприклад, блимання світлодіодом)
        Error_Handler();
    }
    
}
