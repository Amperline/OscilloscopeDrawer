#include "XPT2046/XPT2046.h"
#include "LCD/lcd_driver.h"
#include <stdint.h>

uint8_t xpt2046_write_byte(uint8_t chData)
{
		uint8_t r_val;
		HAL_SPI_TransmitReceive(&hspi1,&chData,&r_val,1,0xff);
    return r_val;
}


void xpt2046_init(void)
{		
	__XPT2046_CS_SET();
}

uint16_t xpt2046_read_ad_value(uint8_t chCmd)
{
    uint16_t hwData = 0;
    
    __XPT2046_CS_CLR();
    xpt2046_write_byte(chCmd);
    hwData = xpt2046_write_byte(0x00);
    hwData <<= 8;
    hwData |= xpt2046_write_byte(0x00);
    hwData >>= 4;
   __XPT2046_CS_SET();
    
    return hwData;
}

#define READ_TIMES  5
#define LOST_NUM    1
uint16_t xpt2046_read_average(uint8_t chCmd)
{
    uint8_t i, j;
    uint16_t hwbuffer[READ_TIMES], hwSum = 0, hwTemp;

    for (i = 0; i < READ_TIMES; i ++) {
        hwbuffer[i] = xpt2046_read_ad_value(chCmd);
    }
    for (i = 0; i < READ_TIMES - 1; i ++) {
        for (j = i + 1; j < READ_TIMES; j ++) {
            if (hwbuffer[i] > hwbuffer[j]) {
                hwTemp = hwbuffer[i];
                hwbuffer[i] = hwbuffer[j];
                hwbuffer[j] = hwTemp;
            }
        }
    }
    for (i = LOST_NUM; i < READ_TIMES - LOST_NUM; i ++) {
        hwSum += hwbuffer[i];
    }
    hwTemp = hwSum / (READ_TIMES - 2 * LOST_NUM);

    return hwTemp;
}

#define DAC_X_XPT_MAX 2050
#define DAC_X_XPT_MIN 250
#define DAC_Y_XPT_MAX 2000
#define DAC_Y_XPT_MIN 150

void xpt2046_read_xy(uint16_t *phwXpos, uint16_t *phwYpos)
{
    uint16_t raw_x = xpt2046_read_average(0xD0);
    uint16_t raw_y = xpt2046_read_average(0x90);

    // 2. Адаптуємо координати під альбомну орієнтацію (setRotation(1))
    // Міняємо осі місцями та інвертуємо X (який став Y)
    *phwXpos = DAC_X_XPT_MAX - raw_y;
    if(*phwXpos > DAC_X_XPT_MAX)
        *phwXpos = 0;
    // *phwYpos = 4095 - raw_x;
    *phwYpos = raw_x;

    if(*phwYpos > DAC_Y_XPT_MAX)
        *phwYpos = 0;
}
//320x240pix
void xtp2046_read_xy_inPixels(uint16_t *pXpix, uint16_t *pYpix)
{
    uint16_t raw_x = 0;
    uint16_t raw_y = 0;
    xpt2046_twice_read_xy(&raw_x, &raw_y);

    *pXpix = ((uint32_t)abs(raw_x - DAC_X_XPT_MIN) * LCD_WIDTH) / (DAC_X_XPT_MAX - DAC_X_XPT_MIN);
    *pYpix = ((uint32_t)abs(raw_y - DAC_Y_XPT_MIN) * LCD_HEIGHT) / (DAC_Y_XPT_MAX - DAC_Y_XPT_MIN);

}

#define ERR_RANGE 50
bool xpt2046_twice_read_xy(uint16_t *phwXpos, uint16_t *phwYpos)
{
	uint16_t hwXpos1, hwYpos1, hwXpos2, hwYpos2;

	xpt2046_read_xy(&hwXpos1, &hwYpos1);
	xpt2046_read_xy(&hwXpos2, &hwYpos2);

	if (((hwXpos2 <= hwXpos1 && hwXpos1 < hwXpos2 + ERR_RANGE) || (hwXpos1 <= hwXpos2 && hwXpos2 < hwXpos1 + ERR_RANGE))
	&& ((hwYpos2 <= hwYpos1 && hwYpos1 < hwYpos2 + ERR_RANGE) || (hwYpos1 <= hwYpos2 && hwYpos2 < hwYpos1 + ERR_RANGE))) {
		*phwXpos = (hwXpos1 + hwXpos2) / 2;
		*phwYpos = (hwYpos1 + hwYpos2) / 2;
		return true;
	}

	return false;
}


