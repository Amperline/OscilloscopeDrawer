cmake_minimum_required(VERSION 3.10)
#project(Lab1 C CXX) Вказуємо мови одразу
include(${CMAKE_SOURCE_DIR}/CmakeConfigs/Cfg_definitions.cmake)
include(${CMAKE_SOURCE_DIR}/CmakeConfigs/Cfg_Compiler.cmake)

project(OSCLLSCP_drawer C)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 17) 
set(CMAKE_C_STANDARD 11)

# 3. Прапори компіляції та ЛІНКУВАННЯ
# Додаємо -g для дебагу в Proteus
set(AVR_FLAGS "-mmcu=${MCU} -DF_CPU=${F_CPU} -Os -g")

set(CMAKE_C_FLAGS "${AVR_FLAGS}")
set(CMAKE_CXX_FLAGS "${AVR_FLAGS}")
# Дуже важливо: лінкер теж має знати про -mmcu!
set(CMAKE_EXE_LINKER_FLAGS "-mmcu=${MCU}") 

# 4. Вихідні файли
set(SOURCE src/main.c)

include_directories(
    ${AVR_TOOLCHAIN}/avr/include
    ${CMAKE_SOURCE_DIR}/headers
)

add_executable(${PROJECT_NAME}.elf ${SOURCE}) # Робимо розширення .elf для дебагу

target_link_libraries(${PROJECT_NAME}.elf ${ALL_LIBRARIES})

# 5. Створення HEX для Proteus
# Використовуємо $<TARGET_FILE...>, щоб CMake сам знав шлях до файлу
add_custom_command(TARGET ${PROJECT_NAME}.elf POST_BUILD
    COMMAND ${AVR_OBJCOPY} -O ihex -R .eeprom $<TARGET_FILE:${PROJECT_NAME}.elf> ${PROJECT_NAME}.hex
    COMMENT "Generating HEX file for Proteus..."
)

#avrdude -c <програматор> -p <мікроконтролер> -P <порт> -U flash:w:firmware.hex:i
#avrdude -c usbasp -p m16 -U flash:w:OSCLLSCP_drawer.hex:i
