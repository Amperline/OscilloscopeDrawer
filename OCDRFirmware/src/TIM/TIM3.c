#include "TIM/TIM3.h"
#include "Error_Handler.h"
#include "stm32f4xx_hal_tim.h"

// Глобальний дескриптор таймера
TIM_HandleTypeDef htim3 = {0};

// // every 31.25 us
// void TIM3_Init(void)
// {
//     __HAL_RCC_TIM3_CLK_ENABLE();

//     htim3.Instance = TIM3;

//     // Prescaler = 0 -> частота таймера залишається 84 МГц 
//     // (1 тік = 1/84 мкс)
//     htim3.Init.Prescaler = 0; 
    
//     htim3.Init.CounterMode = TIM_COUNTERMODE_UP;

//     // ARR = 2625 - 1 -> цикл триває 2625 тіків (рівно 31.25 мкс)
//     // Це відповідає частоті переривань 32 кГц
//     htim3.Init.Period = 2625 - 1;

//     htim3.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1; 
//     htim3.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;

//     // Ініціалізація базового таймера
//     if (HAL_TIM_Base_Init(&htim3) != HAL_OK)
//     {
//         Error_Handler();
//     }

//     // --- Налаштування переривань (NVIC) ---
//     // Пріоритет (0 - найвищий). Налаштуйте відповідно до вашої архітектури
// }

void TIM3_Init(void)
{
    __HAL_RCC_TIM3_CLK_ENABLE();
    htim3.Instance = TIM3;
    
    // htim3.Init.Prescaler = 21 - 1; 
    // htim3.Init.Period = 125 - 1;

    htim3.Init.Prescaler = 42 - 1; 
    htim3.Init.Period = 625 - 1;

    htim3.Init.CounterMode = TIM_COUNTERMODE_UP;
    htim3.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1; 
    htim3.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;

    if (HAL_TIM_Base_Init(&htim3) != HAL_OK)
    {
        Error_Handler();
    }
}