cmake_minimum_required(VERSION 3.17)

# initialize the SDK based on PICO_SDK_PATH
# note: this must happen before project()
include(include/pico-sdk/pico_sdk_init.cmake)

project(low-level-nav)
set(CMAKE_BUILD_TYPE Debug)


add_executable(${PROJECT_NAME} ${CMAKE_CURRENT_SOURCE_DIR}/src/low-level-navigator.cpp)

target_include_directories(
${PROJECT_NAME} 
PUBLIC 
${CMAKE_CURRENT_SOURCE_DIR}/src/
${CMAKE_CURRENT_SOURCE_DIR}/src/high_level_drivers/
${CMAKE_CURRENT_SOURCE_DIR}/src/hardware_configurations/
)

target_link_directories(
    ${PROJECT_NAME}
    PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/src/
    ${CMAKE_CURRENT_SOURCE_DIR}/src/high_level_drivers/
    ${CMAKE_CURRENT_SOURCE_DIR}/src/hardware_configurations/
    )

target_sources(
    ${PROJECT_NAME}
    PUBLIC     
    ${CMAKE_CURRENT_SOURCE_DIR}/src/low-level-navigator.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/high_level_drivers/propulsion_engine.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/hardware_configurations/configuration_1.cpp
)

# initialize the Raspberry Pi Pico SDK
pico_sdk_init()


target_link_libraries(${PROJECT_NAME}
  pico_stdlib
  hardware_pwm)

  target_compile_definitions(${PROJECT_NAME} PRIVATE
	PICO_DEFAULT_UART_TX_PIN=16
	PICO_DEFAULT_UART_RX_PIN=17
	)

pico_enable_stdio_usb(${PROJECT_NAME} 0)
pico_enable_stdio_uart(${PROJECT_NAME} 1)

# create map/bin/hex/uf2 file in addition to ELF.
pico_add_extra_outputs(${PROJECT_NAME})
