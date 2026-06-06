#include <avr/io.h> 


#include "init_All.h"
#include "pin_def.h"

// 4. Важливий нюанс щодо тачскріна (XPT2046)
// Твій шилд має два пристрої на одній шині SPI: LCD та Touch.

// Коли хочеш малювати: LCD_CS = 0, TP_CS = 1.

// Коли хочеш читати координати: LCD_CS = 1, TP_CS = 0.





int main() {
  init_spi();
  init_lcd();


  uint8_t a;


  while (1) {

  }

  return 0;
}
