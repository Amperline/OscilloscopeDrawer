#include "lcd.h"
#include "pin_def.h"

void lcd_fill_screen(uint16_t color) {
    // Встановлюємо вікно на весь екран (якщо не зробили в ініціалізації)
    // ... CASET та RASET ...

    lcd_write_cmd(0x2C); // Починаємо запис у пам'ять
    
    PORTD |= (1 << _PIN_LCD_DC);  // DC = 1 (Передаємо тільки дані)
    PORTB &= ~(1 << _PIN_LCD_CS); // CS = 0
    
    for (uint32_t i = 0; i < 320UL * 240UL; i++) {
        spi_transfer(color >> 8);   // Старший байт
        spi_transfer(color & 0xFF); // Молодший байт
    }
    
    PORTB |= (1 << _PIN_LCD_CS);  // CS = 1
}