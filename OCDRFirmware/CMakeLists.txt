cmake_minimum_required(VERSION 3.20)

set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_PROCESSOR cortex-m4)

set(LINKER_SCRIPT ${CMAKE_SOURCE_DIR}/linker.ld)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include(${CMAKE_SOURCE_DIR}/CmakeConfigs/Cfg_compiler.cmake)
include(${CMAKE_SOURCE_DIR}/CmakeConfigs/Cfg_definitions.cmake)

# заборонити тестову програму для компілятора
set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)

project(${PROJECT_NAME} C CXX ASM)
set(CMAKE_C_STANDARD 17)

file(GLOB HAL_SOURCES
    "${STM_LIB_DIR}/Drivers/STM32F4xx_HAL_Driver/Src/*.c"
    "${STM_LIB_DIR}/Drivers/STM32F4xx_HAL_Driver/Src/Legacy/*.c"

    #трохи з CMSIS
    "${STM_LIB_DIR}/Drivers/CMSIS/Device/ST/STM32F4xx/Source/Templates/system_stm32f4xx.c"
)

# Видаляємо всі шаблони timebase (TIM, RTC, etc)
list(FILTER HAL_SOURCES EXCLUDE REGEX ".*_timebase_.*_template.c$")
# бо в мне кастом src/stm32f4xx_hal_timebase_tim.c

list(FILTER HAL_SOURCES EXCLUDE REGEX ".*system_stm32f4xx.c$")

file(GLOB FREE_RTOS_SOURCES
    "${STM_LIB_DIR}/Middlewares/Third_Party/FreeRTOS/Source/*.c"
    "${STM_LIB_DIR}/Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F/*.c"
)
file(GLOB TIMS
    "${CMAKE_SOURCE_DIR}/src/TIM/*.c"
)

file(GLOB COMMS
    "${CMAKE_SOURCE_DIR}/src/comm/*.c"
)

file(GLOB M_GEN
    "${CMAKE_SOURCE_DIR}/src/general/*.c"
)

set(SOURCE
    src/main.c
    src/stm32_assert.c
    src/stubs.c
    src/def.c

    src/stm32f4xx_hal_timebase_tim.c
    src/system_stm32f4xx.c
    src/stm32f4xx_it.c #interrupts
    src/syscalls.c
    src/sysmem.c
    src/Error_Handler.c
    startup_stm.s
    ${HAL_SOURCES}
    
    ${TIMS}
    ${COMMS}
    ${M_GEN}
     
    ${FREE_RTOS_SOURCES}
    ${STM_LIB_DIR}/Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F/port.c
    ${STM_LIB_DIR}/Middlewares/Third_Party/FreeRTOS/Source/portable/MemMang/heap_4.c
    ${STM_LIB_DIR}/Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS/cmsis_os.c

    Drivers/Fonts/Fonts.c
    Drivers/LCD/lcd_driver.c
    Drivers/Touch/Touch.c
    Drivers/XPT2046/XPT2046.c
)

set(HEADERS
    headers/stm32f4xx_it.h #interrupts
    headers/stm32f4xx_hal_conf.h
    headers/stm32_assert.h
    headers/def.h
    headers/TIM/TIM3.h
    headers/TIM/TIM5.h
    headers/Error_Handler.h
    headers/FreeRTOSConfig.h
    
    headers/comm/i2c.h
    headers/comm/spi.h
    headers/comm/usart.h

    headers/general/dotsEv.h
    headers/general/tasks.h
    headers/general/touchM.h
    headers/general/DAC.h
    headers/general/menu.h

    Drivers/Fonts/Fonts.h
    Drivers/LCD/lcd_driver.h
    Drivers/Touch/Touch.h
    Drivers/XPT2046/XPT2046.h
)

include_directories(
    ${STM_LIB_DIR}/Drivers/CMSIS/Include
    ${STM_LIB_DIR}/Drivers/CMSIS/Core/Include
    ${STM_LIB_DIR}/Drivers/CMSIS/Device/ST/STM32F4xx/Include
    ${STM_LIB_DIR}/Drivers/STM32F4xx_HAL_Driver/Inc
    ${CMAKE_SOURCE_DIR}/headers
    ${CMAKE_SOURCE_DIR}/Drivers

    ${STM_LIB_DIR}/Middlewares/Third_Party/FreeRTOS/Source/include
    ${STM_LIB_DIR}/Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F
    ${STM_LIB_DIR}/Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS
)

add_executable(${PROJECT_NAME}.elf ${SOURCE} ${HEADERS})

target_compile_definitions(${PROJECT_NAME}.elf PRIVATE STM32F401xC USE_HAL_DRIVER)
# add_definitions(-DSTM32F401xC -DUSE_HAL_DRIVER)

target_link_options(${PROJECT_NAME}.elf PRIVATE
    "-T${LINKER_SCRIPT}"
)

target_link_libraries(${PROJECT_NAME}.elf ${ALL_LIBRARIES} m)

include(${CMAKE_SOURCE_DIR}/CmakeConfigs/Cfg_PostBUILD.cmake)