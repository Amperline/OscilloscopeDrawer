if(WIN32)

# 2. Компілятори (якщо вони в PATH, CMake їх знайде)
set(CMAKE_C_COMPILER "${AVR_TOOLCHAIN}/bin/avr-gcc.exe")
set(CMAKE_CXX_COMPILER "${AVR_TOOLCHAIN}/bin/avr-g++.exe")

# Вказуємо шлях до утиліти, яка робить HEX
set(AVR_OBJCOPY "${AVR_TOOLCHAIN}/bin/avr-objcopy.exe")

elseif(UNIX)
# Компілятори для Linux (знаходяться автоматично, бо лежать у /usr/bin)
    set(CMAKE_C_COMPILER avr-gcc)
    set(CMAKE_CXX_COMPILER avr-g++)

    # Утиліта для створення HEX-файлу
    set(AVR_OBJCOPY avr-objcopy)

endif()

