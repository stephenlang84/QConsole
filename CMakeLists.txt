cmake_minimum_required(VERSION 3.10)

project(QConsole)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 COMPONENTS Core REQUIRED)

if (WIN32)
    set(SOURCES
        qconsole.cpp
        readthread_win.cpp
    )
else()
    set(SOURCES
        qconsole.cpp
    )
endif()

if (WIN32)
    set(HEADERS
        qconsole.h
        readthread_win.h
    )
else()
    set(HEADERS
        qconsole.h
    )
endif()

include_directories(${HEADERS})

add_library(QConsole STATIC ${SOURCES})

target_link_libraries(QConsole PRIVATE Qt6::Core)

target_include_directories(QConsole PUBLIC include)

add_custom_command(TARGET QConsole POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E make_directory "${OUTPUT_PATH}/QConsole/lib"
    COMMAND ${CMAKE_COMMAND} -E make_directory "${OUTPUT_PATH}/QConsole/include"
    COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:QConsole> "${OUTPUT_PATH}/QConsole/lib"
    COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_SOURCE_DIR}/qconsole.h "${OUTPUT_PATH}/QConsole/include"
)