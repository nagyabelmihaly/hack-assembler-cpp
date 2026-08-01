#include <string>

#include <gtest/gtest.h>

#include "Code.hpp"

TEST(CodeTest, Dest_0_EmptyReturns000)
{
    EXPECT_EQ(Code::dest(""), "000");
}

TEST(CodeTest, Dest_1_MReturns001)
{
    EXPECT_EQ(Code::dest("M"), "001");
}

TEST(CodeTest, Dest_2_DReturns010)
{
    EXPECT_EQ(Code::dest("D"), "010");
}

TEST(CodeTest, Dest_3_MDReturns011)
{
    EXPECT_EQ(Code::dest("MD"), "011");
}

TEST(CodeTest, Dest_4_AReturns100)
{
    EXPECT_EQ(Code::dest("A"), "100");
}

TEST(CodeTest, Dest_5_AMReturns101)
{
    EXPECT_EQ(Code::dest("AM"), "101");
}

TEST(CodeTest, Dest_6_ADReturns110)
{
    EXPECT_EQ(Code::dest("AD"), "110");
}

TEST(CodeTest, Dest_7_AMDReturns111)
{
    EXPECT_EQ(Code::dest("AMD"), "111");
}
