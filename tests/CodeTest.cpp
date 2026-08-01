#include <string>

#include <gtest/gtest.h>

#include "Code.hpp"

/* Test cases for Code::dest */

TEST(CodeTest, Dest_0_Empty)
{
    EXPECT_EQ(Code::dest(""), "000");
}

TEST(CodeTest, Dest_1_M)
{
    EXPECT_EQ(Code::dest("M"), "001");
}

TEST(CodeTest, Dest_2_D)
{
    EXPECT_EQ(Code::dest("D"), "010");
}

TEST(CodeTest, Dest_3_MD)
{
    EXPECT_EQ(Code::dest("MD"), "011");
}

TEST(CodeTest, Dest_4_A)
{
    EXPECT_EQ(Code::dest("A"), "100");
}

TEST(CodeTest, Dest_5_AM)
{
    EXPECT_EQ(Code::dest("AM"), "101");
}

TEST(CodeTest, Dest_6_AD)
{
    EXPECT_EQ(Code::dest("AD"), "110");
}

TEST(CodeTest, Dest_7_AMD)
{
    EXPECT_EQ(Code::dest("AMD"), "111");
}

/* Test cases for Code::comp */

TEST(CodeTest, Comp_0_Zero)
{
    EXPECT_EQ(Code::comp("0"), "0101010");
}

TEST(CodeTest, Comp_1_One)
{
    EXPECT_EQ(Code::comp("1"), "0111111");
}

TEST(CodeTest, Comp_2_NegativeOne)
{
    EXPECT_EQ(Code::comp("-1"), "0111010");
}

TEST(CodeTest, Comp_3_D)
{
    EXPECT_EQ(Code::comp("D"), "0001100");
}

TEST(CodeTest, Comp_4_A)
{
    EXPECT_EQ(Code::comp("A"), "0110000");
}

TEST(CodeTest, Comp_5_NotD)
{
    EXPECT_EQ(Code::comp("!D"), "0001101");
}

TEST(CodeTest, Comp_6_NotA)
{
    EXPECT_EQ(Code::comp("!A"), "0110001");
}

TEST(CodeTest, Comp_7_NegativeD)
{
    EXPECT_EQ(Code::comp("-D"), "0001111");
}

TEST(CodeTest, Comp_8_NegativeA)
{
    EXPECT_EQ(Code::comp("-A"), "0110011");
}

TEST(CodeTest, Comp_9_DPlusOne)
{
    EXPECT_EQ(Code::comp("D+1"), "0011111");
}

TEST(CodeTest, Comp_10_APlusOne)
{
    EXPECT_EQ(Code::comp("A+1"), "0110111");
}

TEST(CodeTest, Comp_11_DMinusOne)
{
    EXPECT_EQ(Code::comp("D-1"), "0001110");
}

TEST(CodeTest, Comp_12_AMinusOne)
{
    EXPECT_EQ(Code::comp("A-1"), "0110010");
}

TEST(CodeTest, Comp_13_DPlusA)
{
    EXPECT_EQ(Code::comp("D+A"), "0000010");
}

TEST(CodeTest, Comp_14_DMinusA)
{
    EXPECT_EQ(Code::comp("D-A"), "0010011");
}

TEST(CodeTest, Comp_15_AMinusD)
{
    EXPECT_EQ(Code::comp("A-D"), "0000111");
}

TEST(CodeTest, Comp_16_DAndA)
{
    EXPECT_EQ(Code::comp("D&A"), "0000000");
}

TEST(CodeTest, Comp_17_DOrA)
{
    EXPECT_EQ(Code::comp("D|A"), "0010101");
}

TEST(CodeTest, Comp_18_M)
{
    EXPECT_EQ(Code::comp("M"), "1110000");
}

TEST(CodeTest, Comp_19_NotM)
{
    EXPECT_EQ(Code::comp("!M"), "1110001");
}

TEST(CodeTest, Comp_20_NegativeM)
{
    EXPECT_EQ(Code::comp("-M"), "1110011");
}

TEST(CodeTest, Comp_21_MPlusOne)
{
    EXPECT_EQ(Code::comp("M+1"), "1110111");
}

TEST(CodeTest, Comp_22_MMinusOne)
{
    EXPECT_EQ(Code::comp("M-1"), "1110010");
}

TEST(CodeTest, Comp_23_DPlusM)
{
    EXPECT_EQ(Code::comp("D+M"), "1000010");
}

TEST(CodeTest, Comp_24_DMinusM)
{
    EXPECT_EQ(Code::comp("D-M"), "1010011");
}

TEST(CodeTest, Comp_25_MMinusD)
{
    EXPECT_EQ(Code::comp("M-D"), "1000111");
}

TEST(CodeTest, Comp_26_DAndM)
{
    EXPECT_EQ(Code::comp("D&M"), "1000000");
}

TEST(CodeTest, Comp_27_DOrM)
{
    EXPECT_EQ(Code::comp("D|M"), "1010101");
}

/* Test cases for Code::jump */

TEST(CodeTest, Jump_0_Empty)
{
    EXPECT_EQ(Code::jump(""), "000");
}

TEST(CodeTest, Jump_1_JGT)
{
    EXPECT_EQ(Code::jump("JGT"), "001");
}

TEST(CodeTest, Jump_2_JEQ)
{
    EXPECT_EQ(Code::jump("JEQ"), "010");
}

TEST(CodeTest, Jump_3_JGE)
{
    EXPECT_EQ(Code::jump("JGE"), "011");
}

TEST(CodeTest, Jump_4_JLT)
{
    EXPECT_EQ(Code::jump("JLT"), "100");
}

TEST(CodeTest, Jump_5_JNE)
{
    EXPECT_EQ(Code::jump("JNE"), "101");
}

TEST(CodeTest, Jump_6_JLE)
{
    EXPECT_EQ(Code::jump("JLE"), "110");
}

TEST(CodeTest, Jump_7_JMP)
{
    EXPECT_EQ(Code::jump("JMP"), "111");
}
