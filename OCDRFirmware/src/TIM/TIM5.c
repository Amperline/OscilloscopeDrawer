#include "TIM/TIM5.h"
#include "Error_Handler.h"
#include "def.h"
#include "stm32f4xx_hal_tim.h"
#include <sys/types.h>
#include <stdint.h>
#include <math.h>

// Глобальний дескриптор таймера
TIM_HandleTypeDef htim5;
u_int32_t tim5_ticks_max = 525;

// 84МГц таймер
uint16_t sine_arr[400]; // Масив для синусоїди
uint16_t lut_index = 0; // Поточний індекс

void Generate_Sine_LUT(void)
{
    for(int i = 0; i < 400; i++)
    {
        // Зміщуємо синусоїду вгору (від 0 до 525), центр на 262.5
        // 2 * PI = 6.2831853f
        sine_arr[i] = (uint16_t)(262.5f * (1.0f + sinf(6.2831853f * (float)i / 400.0f)));
    }
}

// Ініціалізація таймера TIM3 у режимі PWM 
// (канал 1 — наприклад, для керування ESC)
void TIM5_Init(void)
{
    // Увімкнемо тактування самого таймера TIM3
    __HAL_RCC_TIM5_CLK_ENABLE();

    htim5.Instance = TIM5;

    // Prescaler (прескалер) — це дільник вхідної тактової частоти таймера.
    // В STM32, значення прескалера в регістрі — це число дільника мінус один.
    // Прескалер рахує від 0 до свого значення, а потім робить поділ.
    htim5.Init.Prescaler = (20 - 1); //21Мгц => ~ 47.619нс => ~ 525 різних заповнень
    
    htim5.Init.CounterMode = TIM_COUNTERMODE_UP;

    // частота 
    // Auto-Reload Register ARR
    htim5.Init.Period = (tim5_ticks_max) - 1;

    // Без ділення внутрішнього таймера (звично для PWM)
    // Звичне ділення вже зроблено
    htim5.Init.ClockDivision = TIM_CLOCKDIVISION_DIV4;

    // Не використовуємо попереднє завантаження ARR (ок для PWM)
    // Вимкнув безпековий захід для ARR з тимчасовим буфером
    htim5.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
    
    // Ініціалізуємо таймер у режимі PWM
    if (HAL_TIM_PWM_Init(&htim5) != HAL_OK)
    {
        Error_Handler();                    // Якщо щось пішло не так — викликати обробник помилки
    }

    // Налаштовуємо канал 1 таймера на PWM
    
    // Структура для налаштування PWM-каналу
    // OC - Output Compare 
    TIM_OC_InitTypeDef sConfigOC = {0};

    // Вибираємо режим PWM1 (сигнал HIGH, поки CNT < CCR)
    sConfigOC.OCMode = TIM_OCMODE_PWM1;
    

    //Початкове значення імпульсу
    sConfigOC.Pulse = 2;

    //1 - високий рівень.
    sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
    sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;

    // Прив'язуємо конфіг каналів до каналу 1 таймера
    if (HAL_TIM_PWM_ConfigChannel(&htim5, &sConfigOC, TIM_CHANNEL_1) != HAL_OK)
    {
        while(1);
    }
}