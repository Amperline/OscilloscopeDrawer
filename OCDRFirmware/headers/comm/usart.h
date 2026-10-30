#ifndef M_USART
#define M_USART

#include "stm32f4xx_hal.h"
#include "stm32f4xx_hal_spi.h"
#include <stdint.h>

extern USART_HandleTypeDef uart1;

void USART_Init();

#endif