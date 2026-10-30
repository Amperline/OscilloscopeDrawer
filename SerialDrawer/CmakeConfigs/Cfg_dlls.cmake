include(${CMAKE_SOURCE_DIR}/CmakeConfigs/Cfg_definitions.cmake)
# message(STATUS "DLL_FILES: ${DLL_FILES}")
# message(STATUS "PROJECT_NAME: ${PROJECT_NAME}")
message(STATUS "OUTPUT_DIR: ${OUTPUT_DIR}")
if(WIN32)
# для QT: &"C:\Qt\6.6.1\mingw_64\bin\windeployqt.exe" TVA_PANEL.exe
    set(WINDEPLOYQT_EXECUTABLE "${QT_DIR}/bin/windeployqt.exe")
    add_custom_command(
    TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${WINDEPLOYQT_EXECUTABLE} "$<TARGET_FILE:${PROJECT_NAME}>"
    COMMENT "Running windeployqt on ${PROJECT_NAME}"
    )
    
    file(GLOB DLL_FILES 
        # "${QT_DIR}/6.6.1/mingw_64/plugins/platforms/*.dll"
    )
    foreach(DLL_FILE ${DLL_FILES})
        add_custom_command(
            TARGET ${PROJECT_NAME} POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
            ${DLL_FILE} ${OUTPUT_DIR}
            )
    endforeach()
elseif(LINUX)
    if(CMAKE_BUILD_TYPE STREQUAL "Debug")
        file(GLOB DLL_FILES "${SFML_DLL_DIR}/*.so*")
        foreach(DLL_FILE ${DLL_FILES})
            add_custom_command(
                TARGET ${PROJECT_NAME} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy_if_different
                ${DLL_FILE} ${OUTPUT_DIR}
                )
        endforeach()
    elseif(CMAKE_BUILD_TYPE STREQUAL "Release")

        file(GLOB DLL_FILES "${SFML_DLL_DIR}/*.so*")
        foreach(DLL_FILE ${DLL_FILES})
            add_custom_command(
                TARGET ${PROJECT_NAME} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy_if_different
                ${DLL_FILE} ${OUTPUT_DIR}
                )
        endforeach()
    endif()
endif()