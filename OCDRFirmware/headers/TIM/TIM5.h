#ifndef _TIM5
#define _TIM5
#include <stm32f4xx_hal.h>
#include <sys/types.h>

extern TIM_HandleTypeDef htim5;
extern u_int32_t tim5_ticks_max;

extern uint16_t sine_arr[400]; // Масив для синусоїди
extern uint16_t lut_index; // Поточний індекс

void TIM5_Init(void);
void Generate_Sine_LUT();

#endif