#ifndef M_SPI
#define M_SPI
#include <avr/io.h>


uint8_t spi_transfer(uint8_t data);

void lcd_write_cmd(uint8_t cmd);

void lcd_write_data(uint8_t data);


#endif