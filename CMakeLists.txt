cmake_minimum_required(VERSION 3.13)

include(pico_sdk_import.cmake)

project(signals)

pico_sdk_init()

add_executable(${PROJECT_NAME} main.cpp signal.cpp intersection.cpp)

pico_enable_stdio_usb(${PROJECT_NAME} 1)

pico_add_extra_outputs(${PROJECT_NAME})

target_link_libraries(${PROJECT_NAME} pico_stdlib pico_multicore)