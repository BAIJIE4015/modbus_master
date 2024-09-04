cmake_minimum_required(VERSION 3.5.0 FATAL_ERROR)
set(CMAKE_BUILD_TYPE Release) 

set(CMAKE_C_COMPILER "/home/Software/gcc-7.5.0/bin/gcc")

set(CMAKE_CXX_COMPILER "/home/Software/gcc-7.5.0/bin/g++")
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
project(modbusmaster VERSION 1.0 LANGUAGES C CXX)
set(TARGET_NAME modbusmaster)

list(APPEND SOURCES
    modbus_master.cpp
)
add_library(${TARGET_NAME} SHARED ${SOURCES})

target_compile_options(${TARGET_NAME} PRIVATE
    "-Os"
    "-ffunction-sections"
    "-fdata-sections"
    "-fvisibility=hidden")
target_link_options(${TARGET_NAME} PRIVATE
    "-Wl,--gc-sections"
    )
