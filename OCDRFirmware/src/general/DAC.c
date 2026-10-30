#include "general/DAC.h"
#include "comm/spi.h"
#include "stm32f401xc.h"
#include "stm32f4xx_hal.h"
#include "stm32f4xx_hal_spi.h"


//0.38us x2 = 0.76us + function = 0.1us
void setVoltage(uint16_t _value)
{
    uint16_t dac_value = ((uint32_t)(4095 * _value) / V_dots);
    
    uint8_t data[2];

    data[0] = (dac_value >> 8) & 0x0F; 
    data[1] = dac_value & 0xFF;  

    while (__HAL_SPI_GET_FLAG(&hspi1, SPI_FLAG_BSY));
    __HAL_SPI_DISABLE(&hspi1);
    MODIFY_REG(hspi1.Instance->CR1, SPI_CR1_BR, SPI_BAUDRATEPRESCALER_4);//21Mhz
    __HAL_SPI_ENABLE(&hspi1);

    // 1. Опускаємо лінію CS (SYNC) в нуль — починаємо транзакцію
    HAL_GPIO_WritePin(DAC_CS_GPIO_Port, DAC_CS_GPIO_Pin, GPIO_PIN_RESET);

    SPI1->DR = data[0];
    while(!(SPI1->SR & SPI_SR_TXE));
    SPI1->DR = data[1];
    while(SPI1->SR & SPI_SR_BSY);

    // 3. Піднімаємо лінію CS (SYNC) в одиницю — ЦАП застосовує напругу
    HAL_GPIO_WritePin(DAC_CS_GPIO_Port, DAC_CS_GPIO_Pin, GPIO_PIN_SET);

    while (__HAL_SPI_GET_FLAG(&hspi1, SPI_FLAG_BSY));
    __HAL_SPI_DISABLE(&hspi1);
    MODIFY_REG(hspi1.Instance->CR1, SPI_CR1_BR, SPI_BAUDRATEPRESCALER_64);
    __HAL_SPI_ENABLE(&hspi1);
}