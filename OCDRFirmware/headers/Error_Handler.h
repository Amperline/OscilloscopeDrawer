#ifndef _ERROR_HANDLER
#define _ERROR_HANDLER

#include <stm32f4xx_hal.h>
#include "FreeRTOS.h"
#include "task.h"
#include <stdio.h>

void Error_Handler(void);
void vApplicationStackOverflowHook(TaskHandle_t xTask, char *pcTaskName);
// void vApplicationStackOverflowHook(void);

#endif