#include <avr/interrupt.h>
#include <avr/io.h>

#include "init.h"
#include "init_All.h"

int main() {

  DDRD = 0b00000001;
  PORTD = 0b00000001;

  while (1) {
    PORTD = 0b00000000;

    PORTD = 0b00000001;
  }
  return 0;
}
