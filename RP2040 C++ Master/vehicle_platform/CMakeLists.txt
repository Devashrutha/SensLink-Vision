cmake_minimum_required(VERSION 3.13)

include(pico_sdk_import.cmake)
include(pimoroni_pico_import.cmake)

project(vehicle C CXX ASM)
set(CMAKE_C STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

pico_sdk_init()

add_executable(vehicle
    vehicle.cpp
)

pico_enable_stdio_usb(vehicle 1)
pico_enable_stdio_uart(vehicle 1)

pico_add_extra_outputs(vehicle)

add_subdirectory(pimoroni-pico/common)
add_subdirectory(pimoroni-pico/drivers/st7735)
add_subdirectory(pimoroni-pico/libraries/pico_graphics)

target_include_directories(vehicle PRIVATE ${CMAKE_CURRENT_LIST_DIR} )
target_link_libraries(vehicle pico_stdlib pico_graphics st7735 hardware_spi)
