cmake_minimum_required(VERSION 3.17)

# initialize the SDK based on PICO_SDK_PATH
# note: this must happen before project()
include(include/pico-sdk/pico_sdk_init.cmake)

project(low-level-nav)
set(CMAKE_BUILD_TYPE Debug)

add_executable(low-level-nav src/low-level-navigator.cpp)
# initialize the Raspberry Pi Pico SDK
pico_sdk_init()

target_include_directories(low-level-nav PRIVATE
  ${CMAKE_CURRENT_LIST_DIR}
  ${CMAKE_CURRENT_LIST_DIR}/.. # for our common lwipopts or any other standard includes, if required
)


target_link_libraries(low-level-nav pico_stdlib)

# create map/bin/hex/uf2 file in addition to ELF.
pico_add_extra_outputs(low-level-nav)
