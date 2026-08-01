#include "stm32f4xx_hal_gpio.h"
//those are offsets

//PORT B
#define _LCD_DC_PIN GPIO_PIN_0
#define _LCD_CS_PIN GPIO_PIN_1
#define _TP_CS_PIN GPIO_PIN_2
#define _SD_CS_PIN GPIO_PIN_4
#define _SCL_PIN GPIO_PIN_6
#define _SDA_PIN GPIO_PIN_7
#define _TP_IRQ_PIN GPIO_PIN_12

//PORT A
#define _PWM_PIN GPIO_PIN_0
#define _SCLK_PIN GPIO_PIN_5
#define _MISO_PIN GPIO_PIN_6
#define _MOSI_PIN GPIO_PIN_7
#define _TX_PIN GPIO_PIN_9
#define _RX_PIN GPIO_PIN_10
#define _FRONT_SYNC_IRQ_PIN GPIO_PIN_3