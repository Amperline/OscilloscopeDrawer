#ifndef M_SPI
#define M_SPI

#include "stm32f4xx_hal.h"
#include "stm32f4xx_hal_spi.h"
#include <stdint.h>

extern SPI_HandleTypeDef hspi1;

void SPI_Init();

// const uint8_t X_com = 0x2A;
// const uint8_t Y_com = 0x2B;
// const uint8_t C_com = 0x2C;


// void set_Pixel(uint16_t X_cord, uint16_t Y_cord, uint8_t R, uint8_t G, uint8_t B);

#endif