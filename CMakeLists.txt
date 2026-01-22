cmake_minimum_required(VERSION 3.20)
project(wordSearch LANGUAGES C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

file(GLOB SRC_FILES src/*.c)

add_executable(wordSearch ${SRC_FILES})

target_include_directories(wordSearch PRIVATE ${PROJECT_SOURCE_DIR}/include)
