#include <avr/io.h>
#include <util/delay.h>
#include "studlib_AVR_atmega16.h"

int main() {
    
    DDRD = 0b00000001;
    PORTD = 0b00000001;
    
    while(1)
    {
        _delay_ms(500);
        PORTD = 0b00000000;
        _delay_ms(500);
        PORTD = 0b00000001;
    }

    return 0;
}