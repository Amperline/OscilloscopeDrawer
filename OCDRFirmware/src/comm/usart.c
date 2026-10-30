#include "comm/usart.h"
#include "Error_Handler.h"
#include "stm32f4xx_hal_usart.h"

USART_HandleTypeDef uart1 = {0};

void USART_Init()
{
    uart1.Init.BaudRate = 9600;
    uart1.Init.CLKLastBit = 0;
    uart1.Init.CLKPhase = 0;
    uart1.Init.CLKPolarity = 0;
    uart1.Init.Mode = 0;
    uart1.Init.Parity = 0;
    uart1.Init.StopBits = 0;
    uart1.Init.WordLength = 0;

    if(HAL_USART_Init(&uart1) != HAL_OK)
    {
        Error_Handler();
    }
}