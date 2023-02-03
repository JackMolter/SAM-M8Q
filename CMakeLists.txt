cmake_minimum_required(VERSION 3.12)

include(pico_sdk_import.cmake)
include_directories(lwgps/src/include)

project(SAM-M8Q)
add_library( gps INTERFACE)

pico_sdk_init()

target_sources(gps INTERFACE
${CMAKE_CURRENT_LIST_DIR}/GPS.c
${CMAKE_CURRENT_LIST_DIR}/lwgps.c

)
add_library(lwgps INTERFACE)
target_sources(lwgps INTERFACE ${CMAKE_CURRENT_LIST_DIR}/src/lwgps/lwgps.c)
target_include_directories(lwgps INTERFACE ${CMAKE_CURRENT_LIST_DIR}/src/include)
target_link_directories(gps INTERFACE /src/include)


target_link_libraries(gps INTERFACE
    pico_stdlib
    hardware_i2c
    hardware_uart
    hardware_spi
    hardware_irq
    hardware_dma
    hardware_pwm
)

add_executable(${PROJECT_NAME})
target_link_libraries(${PROJECT_NAME} gps)
target_compile_definitions(${PROJECT_NAME} PRIVATE gps)

pico_enable_stdio_usb(${PROJECT_NAME} 1) # from video
pico_enable_stdio_uart(${PROJECT_NAME} 0)

pico_add_extra_outputs(${PROJECT_NAME})