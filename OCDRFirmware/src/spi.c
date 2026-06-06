#include "spi.h"
#include "pin_def.h"

uint8_t spi_transfer(uint8_t data) {
    SPDR = data;
    while(!(SPSR & (1 << SPIF))); // Чекаємо завершення передачі
    return SPDR;
}

void lcd_write_cmd(uint8_t cmd) {
    PORTD &= ~(1 << _PIN_LCD_DC); // DC = 0 (Команда)
    PORTB &= ~(1 << _PIN_LCD_CS); // CS = 0 (Активуємо дисплей)
    spi_transfer(cmd);
    PORTB |= (1 << _PIN_LCD_CS);  // CS = 1
}

void lcd_write_data(uint8_t data) {
    PORTD |= (1 << _PIN_LCD_DC);  // DC = 1 (Дані)
    PORTB &= ~(1 << _PIN_LCD_CS); // CS = 0
    spi_transfer(data);
    PORTB |= (1 << _PIN_LCD_CS);  // CS = 1
}
