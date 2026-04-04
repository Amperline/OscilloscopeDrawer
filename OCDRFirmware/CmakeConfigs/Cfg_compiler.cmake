# 2. Компілятори (якщо вони в PATH, CMake їх знайде)
set(CMAKE_C_COMPILER "${AVR_TOOLCHAIN}/bin/avr-gcc.exe")
set(CMAKE_CXX_COMPILER "${AVR_TOOLCHAIN}/bin/avr-g++.exe")

# Вказуємо шлях до утиліти, яка робить HEX
set(AVR_OBJCOPY "${AVR_TOOLCHAIN}/bin/avr-objcopy.exe")