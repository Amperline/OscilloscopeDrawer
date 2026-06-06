#ifndef PIN_DEF
#define PIN_DEF

#include <avr/io.h>
#define F_CPU 8000000U

// SCLK	SPI clock
// MISO	SPI master in slave out
// MOSI	SPI master out slave in
// LCD_CS	LCD chip select signal
// LCD_BL	LCD backlight control signal
// LCD_DC	LCD digital command signal
// SD_CS	SD chip select signal
// TP_CS	XPT2046 chip select signal
// TP_IRQ	XPT2046 interrupt output signal

//PORT A
#define PA0           PA0
#define PA1           PA1
#define PA2           PA2
#define PA3           PA3
#define PA5           PA5
#define PA5           PA5
#define PA6           PA6
#define PA7           PA7

//PORT B
#define PB0           PB0
#define PB1           PB1
#define _PIN_SD_CS    (1<<PB2)
#define _PIN_TP_CS    (1<<PB3)
#define _PIN_LCD_CS   (1<<PB4) //(=1 always)
#define _PIN_MOSI     (1<<PB5)
#define _PIN_MISO     (1<<PB6)
#define _PIN_SCLK     (1<<PB7)

//PORT C
#define PC0           PC0
#define PC1           PC1
#define PC2           PC2
#define PC3           PC3
#define PC5           PC5
#define PC5           PC5
#define PC6           PC6
#define PC7           PC7

//PORT D
#define PD0           (1<<PD0)
#define PD1           PD1
#define _PIN_TP_IRQ   (1<<PD2)
#define PD3           PD3
#define _PIN_LCD_DC   (1<<PD4)
#define PD5           PD5
#define _PIN_LCD_BL   (1<<PD6)
#define PD7           PD7




//MASKs for chip select
#define CS_MASK_LCD ~(_PIN_LCD_CS)
#define CS_MASK_TP ~(_PIN_TP_CS)

#define CS_CLEAR_ALL (_PIN_LCD_CS | _PIN_SD_CS | _PIN_TP_CS)

//sclk 8 MHz
//MASKs for SPI
#define SPI_control_BASIC_MASK ((1<<SPIE) | (1<<SPE) | (1<<MSTR))
#define SPI_control_LCD_MASK (SPI_control_BASIC_MASK)
#define SPI_control_TP_MASK (SPI_control_BASIC_MASK | (1<<SPR0))

#define SPI_status_BASIC_MASK 0x01


#endif