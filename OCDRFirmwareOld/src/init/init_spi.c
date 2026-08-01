#include "init_spi.h"
#include "pin_def.h"
#include <avr/io.h>

inline void init_spi(void) {

    DDRB = 0;
    DDRD = 0;

    //out MOSI, SCK, LCD_CS, LCD_DC, LCD_BL
    DDRB |= (_PIN_MOSI | _PIN_SCLK | _PIN_LCD_CS | _PIN_LCD_DC );
    DDRB |= _PIN_SD_CS; //always not selected
    DDRD |= (_PIN_LCD_DC | _PIN_LCD_BL);    
    //in MISO (PB6) та TP_IRQ (PD2)
    
   SPCR = SPI_control_BASIC_MASK;
   SPSR = SPI_status_BASIC_MASK;
}

ISR(SPI_STC_vect)
{

}