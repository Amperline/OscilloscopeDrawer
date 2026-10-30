#ifndef M_DOTS
#define M_DOTS

#include "comm/i2c.h"
#include "def.h"
#include <sys/types.h>

// #define EV_Dots_Size 9760
// //represents every dot's value. and the end of the table
// extern uint8_t evaluated_dots[2][EV_Dots_Size];

#define EV_Dots_Size ((H_dots * V_dots) + H_dots)
//represents every dot's value. and the end of the table
extern uint8_t evaluated_dots[EV_Dots_Size];


void evaluate_Dots();
void checkDotsEvaluation();


#endif