cmake_minimum_required(VERSION 3.20)
project(hack_assembler LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20) 
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# ---- core library: everything except main.cpp ----
add_library(hack_assembler_lib
    src/Code.cpp
)
target_include_directories(hack_assembler_lib PUBLIC src)
target_compile_options(hack_assembler_lib PRIVATE -Wall -Wextra -Wpedantic)

# ---- the actual executable ----
add_executable(hack_assembler src/main.cpp)
target_link_libraries(hack_assembler PRIVATE hack_assembler_lib)

# ---- tests (only built if this is the top-level project) ----
option(BUILD_TESTING_HACK_ASSEMBLER "Build unit tests" ON)
if(BUILD_TESTING_HACK_ASSEMBLER)
    enable_testing()
    add_subdirectory(tests)
endif()