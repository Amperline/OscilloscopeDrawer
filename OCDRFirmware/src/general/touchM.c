#include "general/touchM.h"
#include "LCD/lcd_driver.h"
#include "projdefs.h"
#include <stdint.h>
#include "Error_Handler.h"
#include "Touch/Touch.h"
#include "projdefs.h"
#include "FreeRTOS.h"

uint16_t Xpix = 0;
uint16_t Ypix = 0;

//0false 1true
uint8_t readPixels()
{
	if (!(__XPT2046_IRQ_READ())) {
        xtp2046_read_xy_inPixels(&Xpix, &Ypix);   
        return 1;
	}
    return 0;
}



void c_DrawPoint()
{   
    while (1) {
        if (osMutexWait(spiMutexHandle, osWaitForever) == osOK) {

            if(readPixels())
            {
                lcd_draw_point(Xpix, Ypix, 0x0000);
            }
            osMutexRelease(spiMutexHandle);
        }
        osDelay(10);
    }
}

