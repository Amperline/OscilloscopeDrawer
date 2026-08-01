#include "iCircuits.h"
#include "pin_def.h"

void chip_Select(uint8_t chip)
{       
    PORTB |= CS_CLEAR_ALL;
    if(chip == _PIN_LCD_CS)
    {
        PORTB &= CS_MASK_LCD;
        SPCR = SPI_control_LCD_MASK;
        return;
    }
    //_PIN_TP_CS
    PORTB &= CS_MASK_TP;
    SPCR = SPI_control_TP_MASK;
}