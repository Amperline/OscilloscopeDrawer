#ifndef M_MENU
#define M_MENU

#include "stm32f4xx_hal.h"
#include "stm32f4xx_hal_spi.h"
#include <stdint.h>
#include "LCD/lcd_driver.h"

enum SYS_STATUS
{
    MANUAL,
    PROTOCOL,
    MENU
};

void draw_Menu();

#endif