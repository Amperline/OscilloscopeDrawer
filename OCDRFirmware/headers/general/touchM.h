#ifndef M_TOUCH
#define M_TOUCH

#include "def.h"
#include <stdint.h>
#include <sys/types.h>
#include "Touch/Touch.h"
#include "LCD/lcd_driver.h"
#include "XPT2046/XPT2046.h"

extern uint16_t Xpix;
extern uint16_t Ypix;

uint8_t readPixels();
void c_DrawPoint();

extern uint8_t j;

#endif