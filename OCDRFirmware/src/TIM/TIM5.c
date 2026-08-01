#include "TIM/TIM5.h"

// Глобальний дескриптор таймера
TIM_HandleTypeDef htim5 = {0};

// 84МГц таймер

// Ініціалізація таймера TIM3 у режимі PWM 
// (канал 1 — наприклад, для керування ESC)
void TIM3_Init(void)
{
    // Увімкнемо тактування самого таймера TIM3
    __HAL_RCC_TIM5_CLK_ENABLE();

    htim5.Instance = TIM5;

    // Prescaler (прескалер) — це дільник вхідної тактової частоти таймера.
    // В STM32, значення прескалера в регістрі — це число дільника мінус один.
    // Прескалер рахує від 0 до свого значення, а потім робить поділ.
    htim5.Init.Prescaler = 84 - 1; // = 1 МГц = 1 мкс
    
    htim5.Init.CounterMode = TIM_COUNTERMODE_UP;

     // ARR = 9999 → цикл триває 10000 тік = 10 мс → частота 100 Гц
    // Auto-Reload Register ARR
    htim5.Init.Period = 10000 - 1;

    // Без ділення внутрішнього таймера (звично для PWM)
    // Звичне ділення вже зроблено
    htim5.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1; 

    // Не використовуємо попереднє завантаження ARR (ок для PWM)
    // Вимкнув безпековий захід для ARR з тимчасовим буфером
    htim5.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
    
    // Ініціалізуємо таймер у режимі PWM
    if (HAL_TIM_PWM_Init(&htim5) != HAL_OK)
    {
        while(1);                    // Якщо щось пішло не так — викликати обробник помилки
    }

    // Налаштовуємо канал 1 таймера на PWM
    
    // Структура для налаштування PWM-каналу
    // OC - Output Compare 
    TIM_OC_InitTypeDef sConfigOC = {0};

    // Вибираємо режим PWM1 (сигнал HIGH, поки CNT < CCR)
    sConfigOC.OCMode = TIM_OCMODE_PWM1;    

    //Початкове значення імпульсу
    sConfigOC.Pulse = 0;

    //1 - високий рівень.
    sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
    sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;

    // Прив'язуємо конфіг каналів до каналу 1 таймера
    if (HAL_TIM_PWM_ConfigChannel(&htim5, &sConfigOC, TIM_CHANNEL_1) != HAL_OK)
    {
        while(1);
    }
}