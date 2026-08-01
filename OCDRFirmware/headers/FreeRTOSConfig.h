// #ifndef FREERTOS_CONFIG_H
// #define FREERTOS_CONFIG_H

// #include <stdint.h>

// /* Основні параметри ядра */
// #define configUSE_PREEMPTION                    1
// #define configUSE_IDLE_HOOK                     0
// #define configUSE_TICK_HOOK                     0
// #define configCPU_CLOCK_HZ                      (SystemCoreClock)
// #define configTICK_RATE_HZ                      ((TickType_t)1000)
// #define configMAX_PRIORITIES                    5
// #define configMINIMAL_STACK_SIZE                ((uint16_t)128)
// #define configTOTAL_HEAP_SIZE                   ((size_t)10 * 1024)
// #define configMAX_TASK_NAME_LEN                 16
// #define configUSE_16_BIT_TICKS                  0
// #define configIDLE_SHOULD_YIELD                 1
// #define configUSE_MUTEXES                       1
// #define configUSE_COUNTING_SEMAPHORES           1
// #define configQUEUE_REGISTRY_SIZE               8
// #define configUSE_TASK_NOTIFICATIONS            1
// #define configUSE_TIMERS                        0
// #define configCHECK_FOR_STACK_OVERFLOW          2
// #define configUSE_RECURSIVE_MUTEXES             1
// #define configUSE_PORT_OPTIMISED_TASK_SELECTION 1

// /* Вирівнювання для Cortex-M4F */
// #define portBYTE_ALIGNMENT                      8

// /* Сервісні макроси */
// #define portENTER_CRITICAL()    taskENTER_CRITICAL()
// #define portEXIT_CRITICAL()     taskEXIT_CRITICAL()
// #define portDISABLE_INTERRUPTS()  __disable_irq()
// #define portENABLE_INTERRUPTS()   __enable_irq()

// #endif /* FREERTOS_CONFIG_H */


#ifndef FREERTOS_CONFIG_H
#define FREERTOS_CONFIG_H

#include <stdint.h>
#include <stm32f4xx_hal.h>
extern uint32_t SystemCoreClock;

/* Основні параметри ядра */
#define configUSE_PREEMPTION                    1
#define configUSE_IDLE_HOOK                     0
#define configUSE_TICK_HOOK                     1
#define configCPU_CLOCK_HZ                      (SystemCoreClock)
#define configTICK_RATE_HZ                      1000   // 1 ms
#define configMAX_PRIORITIES                    5
#define configMINIMAL_STACK_SIZE                ((uint16_t)128)
#define configTOTAL_HEAP_SIZE                   ((size_t)10 * 1024)
#define configMAX_TASK_NAME_LEN                 16
#define configUSE_16_BIT_TICKS                  0
#define configIDLE_SHOULD_YIELD                 1
#define configUSE_MUTEXES                       1
#define configUSE_COUNTING_SEMAPHORES           1
#define configQUEUE_REGISTRY_SIZE               8
#define configUSE_TASK_NOTIFICATIONS            1
#define configUSE_TIMERS                        0
#define configCHECK_FOR_STACK_OVERFLOW          1 // не хочу перевірку(тому 1 а не > 1)
#define configUSE_RECURSIVE_MUTEXES             1
#define configUSE_PORT_OPTIMISED_TASK_SELECTION 1

/* Cortex-M4F specific definitions */
#define portBYTE_ALIGNMENT                      8

/* NVIC priority configuration for STM32F4xx */
#define configPRIO_BITS                         4
#define configLIBRARY_LOWEST_INTERRUPT_PRIORITY         15
#define configLIBRARY_MAX_SYSCALL_INTERRUPT_PRIORITY    5
#define configKERNEL_INTERRUPT_PRIORITY ( configLIBRARY_LOWEST_INTERRUPT_PRIORITY << (8 - configPRIO_BITS) )
#define configMAX_SYSCALL_INTERRUPT_PRIORITY ( configLIBRARY_MAX_SYSCALL_INTERRUPT_PRIORITY << (8 - configPRIO_BITS) )


//хендлери, щоб не було конфліктів з HAL.
#define vPortSVCHandler    SVC_Handler
#define xPortPendSVHandler PendSV_Handler
#define xPortSysTickHandler SysTick_Handler


#define INCLUDE_vTaskDelay 1

#endif /* FREERTOS_CONFIG_H */