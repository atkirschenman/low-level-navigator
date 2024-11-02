# Generated Cmake Pico project file

cmake_minimum_required(VERSION 3.13)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# ====================================================================================
set(PICO_BOARD pico2 CACHE STRING "Board type")


# Pull in Raspberry Pi Pico SDK (must be before project)
#set(PICO_TOOLCHAIN_PATH )
set(PICO_SDK_PATH ${CMAKE_SOURCE_DIR}/include/pico-sdk)
set(FREERTOS_KERNEL_PATH ${CMAKE_SOURCE_DIR}/include/FreeRTOS)
#include(${PICO_SDK_PATH}/pico_sdk_init.cmake)
include(cmake/FreeRTOS_Kernel_import.cmake)

project(low-level-navigator C CXX ASM)

set(PICO_CXX_ENABLE_EXCEPTIONS 1)

set(PICO_CXX_ENABLE_RTTI 1)

# Initialise the Raspberry Pi Pico SDK
pico_sdk_init()

# Add executable. Default name is the project name, version 0.1

add_executable(low-level-navigator src/low-level-navigator.cpp )

pico_set_program_name(low-level-navigator "low-level-navigator")
pico_set_program_version(low-level-navigator "0.1")

# Generate PIO header
#pico_generate_pio_header(low-level-navigator ${CMAKE_CURRENT_LIST_DIR}/blink.pio)

# Modify the below lines to enable/disable output over UART/USB
pico_enable_stdio_uart(low-level-navigator 0)
pico_enable_stdio_usb(low-level-navigator 1)

add_library(freertos_config INTERFACE)

target_include_directories(freertos_config SYSTEM
INTERFACE
    ${CMAKE_SOURCE_DIR}/src
)

target_compile_definitions(freertos_config
  INTERFACE
    projCOVERAGE_TEST=0
)

target_link_libraries(low-level-navigator PRIVATE
    pico_async_context_freertos
    FreeRTOS-Kernel-Heap4
    pico_stdlib
    )

target_compile_definitions(low-level-navigator PRIVATE
    configNUMBER_OF_CORES=1
    )
