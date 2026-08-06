include(FetchContent)
FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG v1.17.0
)
# Windows-specific: use the same CRT settings as the rest of the project
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

function(add_gtest_suite name)
    string(TOUPPER ${name} name_upper)
    if(BUILD_${name_upper}_TESTS)
        add_executable(${name}_tests ${ARGN})
        target_link_libraries(${name}_tests PRIVATE hack_assembler_lib GTest::gtest_main)
        target_include_directories(${name}_tests PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../src)
        gtest_discover_tests(${name}_tests)
    endif()
endfunction()

include(GoogleTest)

# ---- per-suite toggles ----
option(BUILD_CODE_TESTS "Build Code unit tests" ON)
option(BUILD_PARSER_TESTS "Build Parser unit tests" ON)
option(BUILD_ASSEMBLER_TESTS "Build HackAssembler unit tests" ON)
option(BUILD_SYMBOL_TABLE_TESTS "Build SymbolTable unit tests" ON)

add_gtest_suite(code CodeTest.cpp)
add_gtest_suite(parser ParserTest.cpp)
add_gtest_suite(symbol_table SymbolTableTest.cpp)

if(BUILD_ASSEMBLER_TESTS)
    add_executable(assembler HackAssemblerTest.cpp)
    target_link_libraries(assembler PRIVATE hack_assembler_lib GTest::gtest_main)
    target_compile_definitions(assembler PRIVATE
        FIXTURES_DIR="${CMAKE_CURRENT_SOURCE_DIR}/fixtures"
    )
    target_include_directories(assembler PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../src)
    gtest_discover_tests(assembler)
endif()
