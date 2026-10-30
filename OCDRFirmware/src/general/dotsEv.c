#include "general/dotsEv.h"
#include "Error_Handler.h"
#include "Legacy/stm32_hal_legacy.h"
#include "def.h"
#include "projdefs.h"
#include <stdint.h>

// uint8_t evaluated_dots[2][EV_Dots_Size];

// void evaluate_Dots()
// {
//     uint16_t currDot = 0;

//     for(uint8_t sec = 0; sec < SECTION_NUM; sec++, currDot = 0)
//     {
//         for(uint8_t i = 0; i < 160; i++)
//         {
//             for (uint8_t j = (sec * 60) ; j < ((sec+1) * 60); j++) {
//                 if(ImageArr[i][j] == 1)
//                 {
//                     evaluated_dots[sec][currDot] = j;
//                     currDot++;
//                 }
//             }
//             evaluated_dots[sec][currDot] = 255;
//             currDot++;
//         }
//         for(;currDot < EV_Dots_Size; currDot++)
//         {
//             evaluated_dots[sec][currDot] = 254;
//         }
//     }
// }


uint8_t evaluated_dots[EV_Dots_Size];

void evaluate_Dots()
{
    uint16_t currDot = 0;

    for(uint8_t i = 0; i < H_dots; i++)
    {
        for (uint8_t j = 0; j < V_dots; j++) {
            if(ImageArr[i][j] == 1)
            {
                evaluated_dots[currDot] = j;
                currDot++;
            }
        }
        evaluated_dots[currDot] = 255;
        currDot++;
    }
    for(;currDot < EV_Dots_Size; currDot++)
    {
        evaluated_dots[currDot] = 254;
    }
}

void checkDotsEvaluation()
{
    while (1) 
    {
        if(dots_are_evaluated == 0)
        {
            if (osMutexWait(dotsArrMutexHandle, osWaitForever) == osOK)
            {
                evaluate_Dots();
                currentDot = 0;
                dots_are_evaluated = 1;

                osMutexRelease(dotsArrMutexHandle);
            }
        }
        osDelay(100);
    }
}