#include "general/menu.h"
#include "LCD/lcd_driver.h"


void draw_Menu()
{

    lcd_draw_rect(0, 0, 319, 39, 0b0000011111100000);

    lcd_draw_point(0, 0, RED);
}