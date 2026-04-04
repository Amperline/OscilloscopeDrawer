set(AVR_TOOLCHAIN "C:/Program Files (x86)/Atmel/AVR Studio 5.1/extensions/Atmel/AVRGCC/3.3.1.27/AVRToolchain")

# set(OUTPUT_DIR ${CMAKE_SOURCE_DIR}/build)
set(ALL_LIBRARIES
    "$ENV{LIBS_E}/studlib_AVR_atmega16/studlib_AVR_atmega16.a"
)

# Налаштування заліза
set(MCU atmega16)
set(F_CPU 8000000UL)

# 1. Налаштування крос-компіляції (ОБОВ'ЯЗКОВО ПЕРЕД project())
set(CMAKE_SYSTEM_NAME Generic)      # Кажемо, що це не Windows/Linux, а "голе залізо"
set(CMAKE_SYSTEM_PROCESSOR avr)

# Це критично важливо! Змушує CMake перевіряти компілятор, створюючи
# стат. бібліотеку, а не .exe. Це дозволяє уникнути помилок лінкера на етапі тесту.
set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)