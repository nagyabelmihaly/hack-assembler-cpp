#include <string>

#include <gtest/gtest.h>

#include "Parser.hpp"

TEST(ParserTest, HasMoreCommands_0_Empty)
{
    std::istringstream input("");
    Parser parser(input);
    EXPECT_FALSE(parser.hasMoreCommands());
}

TEST(ParserTest, HasMoreCommands_1_SingleCommand)
{
    std::string source =
        "D=0;JMP\n";
    std::istringstream input(source);
    Parser parser(input);
    EXPECT_TRUE(parser.hasMoreCommands());
}

TEST(ParserTest, HasMoreCommands_2_MultipleCommands)
{
    std::string source =
        "D=0;JMP\n"
        "@2\n"
        "M=D\n";
    std::istringstream input(source);
    Parser parser(input);
    EXPECT_TRUE(parser.hasMoreCommands());
}

TEST(ParserTest, HasMoreCommands_3_CommentsOnly)
{
    std::string source =
        "// This is a comment\n"
        "// Another comment\n"
        "// Yet another comment\n";
    std::istringstream input(source);
    Parser parser(input);
    EXPECT_FALSE(parser.hasMoreCommands());
}

TEST(ParserTest, HasMoreCommands_4_WhitespaceOnly)
{
    std::string source =
        "   \n"
        "\t\n"
        "  \n";
    std::istringstream input(source);
    Parser parser(input);
    EXPECT_FALSE(parser.hasMoreCommands());
}

TEST(ParserTest, HasMoreCommands_5_WhitespaceAndComments)
{
    std::string source =
        "   // This is a comment\n"
        "\t// Another comment\n"
        "  // Yet another comment\n";
    std::istringstream input(source);
    Parser parser(input);
    EXPECT_FALSE(parser.hasMoreCommands());
}

TEST(ParserTest, HasMoreCommands_6_WhitespaceAndCommands)
{
    std::string source =
        "   // This is a comment\n"
        "\t// Another comment\n"
        "  // Yet another comment\n"
        "@2\n"
        "M=D\n";
    std::istringstream input(source);
    Parser parser(input);
    EXPECT_TRUE(parser.hasMoreCommands());
}
