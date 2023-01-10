cmake_minimum_required(VERSION 3.20)
project(ial21 C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Werror -Wextra -g")


file(GLOB LIB_HEADERS "${PROJECT_SOURCE_DIR}/src/*.h")
file(GLOB LIB_SOURCES "${PROJECT_SOURCE_DIR}/src/*.c")

add_executable(ial21 ${LIB_HEADERS} ${LIB_SOURCES})

