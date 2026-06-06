#include <avr/io.h>

#include "pin_def.h"

inline void init_LCD(void) {
    spi_init(); // Твоя ініціалізація портів та SPI

    // 1. Software Reset
    lcd_write_cmd(0x01); 
    _delay_ms(150);

    // 2. Sleep Out (Пробудження)
    lcd_write_cmd(0x11); 
    _delay_ms(255);

    // 3. Color Mode (Налаштування формату пікселя)
    lcd_write_cmd(0x3A); 
    lcd_write_data(0x55); // 16-бітний колір (5-6-5 RGB)
    _delay_ms(10);

    // 4. MADCTL (Напрямок розгортки та орієнтація)
    lcd_write_cmd(0x36); 
    // 0x00 - портрет, 0x60 - альбомна, 0xA0 - альбомна перевернута
    lcd_write_data(0x00); 

    // 5. CASET (Column Address Set - 0 до 239)
    lcd_write_cmd(0x2A);
    lcd_write_data(0x00); lcd_write_data(0x00);
    lcd_write_data(0x00); lcd_write_data(0xEF);

    // 6. RASET (Row Address Set - 0 до 319)
    lcd_write_cmd(0x2B);
    lcd_write_data(0x00); lcd_write_data(0x00);
    lcd_write_data(0x01); lcd_write_data(0x3F);

    // 7. Inversion On (Критично для більшості IPS шилдів)
    // Якщо кольори будуть "негативними", заміни на 0x20 (Inversion Off)
    lcd_write_cmd(0x21); 
    _delay_ms(10);

    // 8. Normal Display Mode On
    lcd_write_cmd(0x13); 
    _delay_ms(10);

    // 9. Display ON (Фінальний акорд)
    lcd_write_cmd(0x29); 
    _delay_ms(150);
}