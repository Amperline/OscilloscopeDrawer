#include "Error_Handler.h"

void Error_Handler(void)
{
    // Зупинити програму або мигати світлодіодом
    while (1)
    {
        HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_13);
        HAL_Delay(500);
    }
}


// Хук для системного тіку (викликається кожну мілісекунду)
void vApplicationTickHook(void)
{
    // Тут можна додати код, який має виконуватися при кожному тіку RTOS,
    // але найчастіше функцію просто залишають порожньою.
}

// Хук для перевірки переповнення стека завдань
void vApplicationStackOverflowHook(TaskHandle_t xTask, char *pcTaskName)
{
    // Якщо стек будь-якого завдання переповниться, програма застрягне тут. 
    // Це дуже корисно для відлагодження.
    while (1)
    {
    }
}