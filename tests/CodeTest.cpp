#include <string>

#include <gtest/gtest.h>

#include "Code.hpp"

TEST(CodeTest, DestMReturns001) {
    Code code;
    const std::string actual = code.dest("M");

    EXPECT_EQ(actual, "001");
}
