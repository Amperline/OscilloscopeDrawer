include(${CMAKE_SOURCE_DIR}/CmakeConfigs/Cfg_definitions.cmake)
# message(STATUS "DLL_FILES: ${DLL_FILES}")
# message(STATUS "PROJECT_NAME: ${PROJECT_NAME}")
message(STATUS "OUTPUT_DIR: ${OUTPUT_DIR}")

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    set(HEX_FILE ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}.hex)
    set(TMP_HEX_FILE ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}.tmp.hex)

    add_custom_command(TARGET ${PROJECT_NAME}.elf POST_BUILD
        COMMAND ${CMAKE_OBJCOPY} -O ihex
                $<TARGET_FILE:${PROJECT_NAME}.elf>
                ${TMP_HEX_FILE}
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
                ${TMP_HEX_FILE}
                ${HEX_FILE}
        COMMAND ${CMAKE_COMMAND} -E remove -f
                ${TMP_HEX_FILE}
        COMMENT "Generating HEX file from ELF (only if different)"
    )
elseif(CMAKE_BUILD_TYPE STREQUAL "Release")

    # file(GLOB DLL_FILES "${SFML_DLL_DIR}/*.dll")
    # foreach(DLL_FILE ${DLL_FILES})
    #     add_custom_command(
    #         TARGET ${PROJECT_NAME} POST_BUILD
    #         COMMAND ${CMAKE_COMMAND} -E copy_if_different
    #         ${DLL_FILE} ${OUTPUT_DIR}
    #         )
    # endforeach()
endif()

#дозволяє після збірки залити HEX файл(прошивку) в МК
add_custom_target(flash
    COMMAND STM32_Programmer_CLI.exe -c port=SWD -d ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}.hex -rst
    COMMENT "Flashing ${PROJECT_NAME} to STM32"
)