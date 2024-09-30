cmake_minimum_required(VERSION 3.10)

project(Demo)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 COMPONENTS Core REQUIRED)

# Set the source files
set(SOURCES
    main.cpp
)

# Add a custom target for prebuild
add_custom_target(prebuildQConsole
    COMMAND ${CMAKE_COMMAND} -E echo "Running prebuildQConsole script..."
    COMMAND ${CMAKE_SOURCE_DIR}/../build-win.bat ${CMAKE_PREFIX_PATH} ${CMAKE_BINARY_DIR}/libs
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/../
)

include_directories(${CMAKE_BINARY_DIR}/libs/QConsole/include)

link_directories(${CMAKE_BINARY_DIR}/libs/QConsole/lib) 

# Add an executable
add_executable(Demo main.cpp)

add_dependencies(Demo prebuildQConsole)

target_link_libraries(Demo PRIVATE Qt6::Core PUBLIC QConsole)
