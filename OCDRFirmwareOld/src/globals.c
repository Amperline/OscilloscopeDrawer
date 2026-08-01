#include "globals.h"
#include "pin_def.h"
#include <avr/io.h>

//curr_CS_State LCD or TP
//used for logic not init
uint8_t curr_CS_State = 0;
//uint8_t spi_READ_done = 0;