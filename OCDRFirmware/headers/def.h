#ifndef _DEF
#define _DEF

#include <stdint.h>
#include <stm32f4xx_hal.h>
#include <sys/_types.h>
#include <sys/types.h>
#include "cmsis_os.h"
//those are offsets

//PORT B


//PORT A
#define _PWM_PIN GPIO_PIN_0
#define _SCLK_PIN GPIO_PIN_5
#define _MISO_PIN GPIO_PIN_6
#define _MOSI_PIN GPIO_PIN_7
#define _TX_PIN GPIO_PIN_9
#define _RX_PIN GPIO_PIN_10

//
#define _FRONT_SYNC_IRQ_PIN GPIO_PIN_3
#define _FRONT_SYNC_IRQ_Port GPIOA

#define LCD_DC_Pin GPIO_PIN_0
#define LCD_DC_GPIO_Port GPIOB//
#define XPT2046_IRQ_Pin GPIO_PIN_12
#define XPT2046_IRQ_GPIO_Port GPIOB//

#define SD_CS_Pin GPIO_PIN_4//not used
#define SD_CS_GPIO_Port GPIOB

#define DAC_CS_GPIO_Pin GPIO_PIN_4
#define DAC_CS_GPIO_Port GPIOB
#define XPT2046_CS_Pin GPIO_PIN_2
#define XPT2046_CS_GPIO_Port GPIOB
#define LCD_CS_Pin GPIO_PIN_1
#define LCD_CS_GPIO_Port GPIOB
#define SD_SPI_HANDLE hspi1

#define LCD_BL_Pin GPIO_PIN_7
#define LCD_BL_GPIO_Port GPIOC



#define V_dots 120
#define H_dots 160
#define SECTION_NUM 2

#define pi (double)3.14159265359

//in ms
extern const u_int16_t time_per_div[2];

// white = 0, black = 1
// WelcomeImageArr[x][y]: x = стовпець (0..319, зліва направо)
//                        y = рядок (0..239, знизу вгору)
extern uint8_t ImageArr[H_dots][V_dots];
extern uint8_t dots_are_evaluated;

extern volatile uint8_t touch_flag;
extern volatile uint8_t sync_flag;

extern uint16_t currentDot;

#define timePerDiv0 0
#define timePerDiv1 1
#define h_divs 10u

extern osMutexId spiMutexHandle;
extern osMutexId dotsArrMutexHandle;
extern osMutexId syncMutexHandle;

#endif