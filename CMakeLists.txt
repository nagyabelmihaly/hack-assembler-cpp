cmake_minimum_required(VERSION 3.20)
project(hobby_asm LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_executable(hack_assembler src/main.cpp)
target_compile_options(hack_assembler PRIVATE -Wall -Wextra -Wpedantic)
