#ifndef M_I2C
#define M_I2C

#include "stm32f4xx_hal.h"
#include "stm32f4xx_hal_i2c.h"

extern I2C_HandleTypeDef hi2c;
void I2C_Init();

#endif