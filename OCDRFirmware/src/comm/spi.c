#include "comm/spi.h"
#include "Legacy/stm32_hal_legacy.h"
#include "stm32f4xx_hal_rcc.h"
#include "stm32f4xx_hal_spi.h"
#include "Error_Handler.h"
#include <stdint.h>

SPI_HandleTypeDef hspi1 = {0};

SPI_HandleTypeDef hspi1;

/* SPI1 init function */
void SPI_Init(void)
{

  hspi1.Instance = SPI1;
  hspi1.Init.Mode = SPI_MODE_MASTER;
  hspi1.Init.Direction = SPI_DIRECTION_2LINES;
  hspi1.Init.DataSize = SPI_DATASIZE_8BIT;
  hspi1.Init.CLKPolarity = SPI_POLARITY_LOW;
  hspi1.Init.CLKPhase = SPI_PHASE_1EDGE;
  hspi1.Init.NSS = SPI_NSS_SOFT;
  hspi1.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_64;
  hspi1.Init.FirstBit = SPI_FIRSTBIT_MSB;
  hspi1.Init.TIMode = SPI_TIMODE_DISABLE;
  hspi1.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
  hspi1.Init.CRCPolynomial = 10;

  if (HAL_SPI_Init(&hspi1) != HAL_OK)
  {
    Error_Handler();
  }

}

// void set_Pixel(uint16_t X_cord, uint16_t Y_cord, uint8_t R, uint8_t G, uint8_t B)
// {
//     HAL_SPI_Transmit(&hspi1, &X_com, sizeof(uint8_t), 1);
//     HAL_SPI_Transmit(&hspi1, &Y_com, sizeof(uint8_t), 1);
//     HAL_SPI_Transmit(&hspi1, &C_com, sizeof(uint8_t), 1);

// }