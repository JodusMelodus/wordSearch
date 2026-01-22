cmake_minimum_required(VERSION 3.20)
project(terra LANGUAGES C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

file(GLOB SRC_FILES src/*.c)

add_executable(terra ${SRC_FILES})

target_include_directories(terra PRIVATE include)

target_include_directories(terra PRIVATE ${PROJECT_SOURCE_DIR}/include)
