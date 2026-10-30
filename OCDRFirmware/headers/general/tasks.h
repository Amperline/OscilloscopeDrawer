#ifndef M_TASKS
#define M_TASKS

#include "def.h"
#include <sys/types.h>

void checkOnTouch();

extern TaskHandle_t dacTaskHandle;
void dacPerform();

void checkOnSync();

#endif