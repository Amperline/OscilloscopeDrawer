#include "general/tasks.h"
#include "Error_Handler.h"
#include "def.h"
#include "Touch/Touch.h"
#include "projdefs.h"
#include <stdint.h>
#include <sys/types.h>


void checkOnTouch()
{   
    while (1) 
    {
        if(touch_flag == 1)
        {
            if (osMutexWait(spiMutexHandle, osWaitForever) == osOK) {
                touch_flag = 0;
                tp_draw_board();

                osMutexRelease(spiMutexHandle);
            }
        }
        osDelay(10);
    }
}

#include "general/dotsEv.h"
#include "general/DAC.h"

uint16_t currentDot = 0;
TaskHandle_t dacTaskHandle = NULL;
void dacPerform()
{
    while (1) {
        
        // 1. Чекаємо сигналу від переривання TIM3 (чекаємо вічно)
        ulTaskNotifyTake(pdTRUE, portMAX_DELAY);
        
        // 2. Тепер ми в контексті задачі і можемо безпечно чекати на м'ютекс!
        if (osMutexWait(spiMutexHandle, osWaitForever) == osOK)
        {
            if(osMutexWait(dotsArrMutexHandle, osWaitForever) == osOK) 
            {
                if(osMutexWait(syncMutexHandle, osWaitForever) == osOK) 
                {
                    if(dots_are_evaluated)
                    {
                        if(currentDot == 0) {
                            setVoltage(120);
                        }
                        
                        while(evaluated_dots[currentDot] != 255)
                        {
                            setVoltage(evaluated_dots[currentDot]);
                            currentDot++;
                            for(uint8_t t = 0; t < 10; t++);
                        }

                        currentDot++;

                        if(evaluated_dots[currentDot] == 254)
                        {
                            currentDot = 0;
                        }
                    }
                    osMutexRelease(syncMutexHandle);
                }
                setVoltage(0);
                osMutexRelease(dotsArrMutexHandle);
            }
            osMutexRelease(spiMutexHandle);
        }
    }
}



void checkOnSync()
{
    while(1)
    {
        if(sync_flag)
        {
            if(osMutexWait(syncMutexHandle, osWaitForever) == osOK)
            {
                currentDot = 0;
                //
                sync_flag = 0;
                osMutexRelease(syncMutexHandle);
            }
        }
        osDelay(5);
    }
}