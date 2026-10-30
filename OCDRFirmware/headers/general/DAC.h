#ifndef M_DAC
#define M_DAC

#include "def.h"
#include <sys/types.h>
#include "comm/spi.h"

void setVoltage(uint16_t _value);

#endif