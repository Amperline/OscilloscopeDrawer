set(PROJECT_NAME "Drawer_PANEL")

if(WIN32 AND DEFINED ENV{Qt6_MinGW_Dir})
    add_definitions(-DWIN32_LEAN_AND_MEAN)
    set(CMAKE_AUTOMOC ON)
    #set(CMAKE_AUTORCC ON)

    #Це врятує від цього
    #include <winsock2.h>
    #include <windows.h>

    # file(TO_CMAKE_PATH "$ENV{Qt6_MinGW_Dir}" QT_DIR)

    set(QT_DIR "$ENV{Qt6_MinGW_Dir}")
    set(SFML_DLL_DIR "${CMAKE_SOURCE_DIR}/libs/SFML/bin/")
    set(SFML_MAIN_DIR "${CMAKE_SOURCE_DIR}/libs/SFML/")
    set(SFML_DIR "${CMAKE_SOURCE_DIR}/libs/SFML/lib/cmake/SFML")
    set(BOOST_DIR "$ENV{BOOST_DIR}")
    set(CMAKE_PREFIX_PATH
        "${QT_DIR}/lib/cmake"
    )
elseif(LINUX)
    set(SFML_DLL_DIR "${CMAKE_SOURCE_DIR}/libs/SFML_linux/bin/")
    set(SFML_MAIN_DIR "${CMAKE_SOURCE_DIR}/libs/SFML_linux/")
    set(SFML_DIR "${CMAKE_SOURCE_DIR}/libs/SFML_linux/lib/cmake/SFML")
else()
    message(FATAL_ERROR "Qt6_MinGW_Dir not set!")
endif()

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    add_compile_definitions(DEBUG)
    set(OUTPUT_DIR ${CMAKE_SOURCE_DIR}/build/Debug)
#     set(SFML_LIBRARIES
#         sfml-graphics-d
#         sfml-window-d
#         sfml-system-d
# )
elseif(CMAKE_BUILD_TYPE STREQUAL "Release")
    set(OUTPUT_DIR ${CMAKE_SOURCE_DIR}/build/Release)
#     set(SFML_LIBRARIES
#         sfml-graphics
#         sfml-window
#         sfml-system
# )
endif()


set(ALL_LIBRARIES)

if(WIN32)
elseif(LINUX)
set(ALL_LIBRARIES ${ALL_LIBRARIES} stdc++)
endif()