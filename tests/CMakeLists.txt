include(FetchContent)
FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG v1.17.0
)
# Windows-specific: use the same CRT settings as the rest of the project
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

add_executable(code_tests
    CodeTest.cpp
)
target_link_libraries(code_tests PRIVATE
    hack_assembler_lib
    GTest::gtest_main
)
target_include_directories(code_tests PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../src)

include(GoogleTest)
gtest_discover_tests(code_tests)
