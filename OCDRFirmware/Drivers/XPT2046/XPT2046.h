#ifndef __XPT2046_H
#define __XPT2046_H

#include <stdint.h>
#include "LCD/lcd_driver.h"

typedef char bool;
#define true 1
#define false 0

extern void xpt2046_init(void);
extern void xpt2046_read_xy(uint16_t *phwXpos, uint16_t *phwYpos);
extern bool xpt2046_twice_read_xy(uint16_t *phwXpos, uint16_t *phwYpos);
extern void xtp2046_read_xy_inPixels(uint16_t *pXpix, uint16_t *pYpix);

#endif



