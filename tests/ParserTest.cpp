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

TEST(ParserTest, Advance_0_SingleCommand)
{
    std::string source =
        "D=D+1;JLT\n";
    std::istringstream input(source);
    Parser parser(input);
    EXPECT_TRUE(parser.hasMoreCommands());
    parser.advance();
    EXPECT_FALSE(parser.hasMoreCommands());
}

TEST(ParserTest, Advance_1_MultipleCommands)
{
    std::string source =
        "@2\n"
        "M=D\n";
    std::istringstream input(source);
    Parser parser(input);
    EXPECT_TRUE(parser.hasMoreCommands());
    parser.advance();
    EXPECT_TRUE(parser.hasMoreCommands());
    parser.advance();
    EXPECT_FALSE(parser.hasMoreCommands());
}

TEST(ParserTest, Advance_2_WhitespaceAndComments)
{
    std::string source =
        "   // This is a comment\n"
        "@2\n"
        "\t// Another comment\n"
        "M=D\n"
        "  // Yet another comment\n";
    std::istringstream input(source);
    Parser parser(input);
    EXPECT_TRUE(parser.hasMoreCommands());
    parser.advance();
    EXPECT_TRUE(parser.hasMoreCommands());
    parser.advance();
    EXPECT_FALSE(parser.hasMoreCommands());
}

TEST(ParserTest, Advance_3_CommandsWithComments)
{
    std::string source =
        "@2 // This is a comment\n"
        "M=D // Another comment\n";
    std::istringstream input(source);
    Parser parser(input);
    EXPECT_TRUE(parser.hasMoreCommands());
    parser.advance();
    EXPECT_TRUE(parser.hasMoreCommands());
    parser.advance();
    EXPECT_FALSE(parser.hasMoreCommands());
}

TEST(ParserTest, Advance_4_CommandsWithWhitespace)
{
    std::string source =
        "   @2   \n"
        "   M=D   \n";
    std::istringstream input(source);
    Parser parser(input);
    EXPECT_TRUE(parser.hasMoreCommands());
    parser.advance();
    EXPECT_TRUE(parser.hasMoreCommands());
    parser.advance();
    EXPECT_FALSE(parser.hasMoreCommands());
}

TEST(ParserTest, CommandType_0_ACommandWithDecimal)
{
    std::string source =
        "@2\n";
    std::istringstream input(source);
    Parser parser(input);
    parser.advance();
    EXPECT_EQ(parser.commandType(), CommandType::A_COMMAND);
}

TEST(ParserTest, CommandType_1_ACommandWithSymbol)
{
    std::string source =
        "@LOOP\n";
    std::istringstream input(source);
    Parser parser(input);
    parser.advance();
    EXPECT_EQ(parser.commandType(), CommandType::A_COMMAND);
}

TEST(ParserTest, CommandType_2_CCommandFull)
{
    std::string source =
        "D=D+1;JLT\n";
    std::istringstream input(source);
    Parser parser(input);
    parser.advance();
    EXPECT_EQ(parser.commandType(), CommandType::C_COMMAND);
}

TEST(ParserTest, CommandType_3_CCommandNoDest)
{
    std::string source =
        "M-1;JNE\n";
    std::istringstream input(source);
    Parser parser(input);
    parser.advance();
    EXPECT_EQ(parser.commandType(), CommandType::C_COMMAND);
}

TEST(ParserTest, CommandType_4_CCommandNoJump)
{
    std::string source =
        "M=D+1\n";
    std::istringstream input(source);
    Parser parser(input);
    parser.advance();
    EXPECT_EQ(parser.commandType(), CommandType::C_COMMAND);
}

TEST(ParserTest, CommandType_5_CCommandOnlyComp)
{
    std::string source =
        "M+1\n";
    std::istringstream input(source);
    Parser parser(input);
    parser.advance();
    EXPECT_EQ(parser.commandType(), CommandType::C_COMMAND);
}

TEST(ParserTest, CommandType_6_LCommand)
{
    std::string source =
        "(LOOP)\n";
    std::istringstream input(source);
    Parser parser(input);
    parser.advance();
    EXPECT_EQ(parser.commandType(), CommandType::L_COMMAND);
}

TEST(ParserTest, Symbol_0_ACommandWithDecimal)
{
    std::string source =
        "@2\n";
    std::istringstream input(source);
    Parser parser(input);
    parser.advance();
    EXPECT_EQ(parser.symbol(), "2");
}

TEST(ParserTest, Symbol_1_ACommandWithSymbolUppercase)
{
    std::string source =
        "@LOOP\n";
    std::istringstream input(source);
    Parser parser(input);
    parser.advance();
    EXPECT_EQ(parser.symbol(), "LOOP");
}

TEST(ParserTest, Symbol_2_ACommandWithSymbolLowercase)
{
    std::string source =
        "@sum\n";
    std::istringstream input(source);
    Parser parser(input);
    parser.advance();
    EXPECT_EQ(parser.symbol(), "sum");
}

TEST(ParserTest, Symbol_3_LCommandWithUppercase)
{
    std::string source =
        "(LOOP)\n";
    std::istringstream input(source);
    Parser parser(input);
    parser.advance();
    EXPECT_EQ(parser.symbol(), "LOOP");
}

TEST(ParserTest, Symbol_4_LCommandWithLowercase)
{
    std::string source =
        "(sum)\n";
    std::istringstream input(source);
    Parser parser(input);
    parser.advance();
    EXPECT_EQ(parser.symbol(), "sum");
}

TEST(ParserTest, Symbol_5_ACommandWithWhitespace)
{
    std::string source =
        "   @2   \n";
    std::istringstream input(source);
    Parser parser(input);
    parser.advance();
    EXPECT_EQ(parser.symbol(), "2");
}

TEST(ParserTest, Symbol_6_LCommandWithWhitespace)
{
    std::string source =
        "   (LOOP)   \n";
    std::istringstream input(source);
    Parser parser(input);
    parser.advance();
    EXPECT_EQ(parser.symbol(), "LOOP");
}

TEST(ParserTest, Symbol_7_ACommandWithComment)
{
    std::string source =
        "@2 // This is a comment\n";
    std::istringstream input(source);
    Parser parser(input);
    parser.advance();
    EXPECT_EQ(parser.symbol(), "2");
}

TEST(ParserTest, Symbol_8_LCommandWithComment)
{
    std::string source =
        "(LOOP) // This is a comment\n";
    std::istringstream input(source);
    Parser parser(input);
    parser.advance();
    EXPECT_EQ(parser.symbol(), "LOOP");
}

TEST(ParserTest, CCommand_0_Full)
{
    std::string source =
        "D=D+1;JLT\n";
    std::istringstream input(source);
    Parser parser(input);
    parser.advance();
    EXPECT_EQ(parser.dest(), "D");
    EXPECT_EQ(parser.comp(), "D+1");
    EXPECT_EQ(parser.jump(), "JLT");
}

TEST(ParserTest, CCommand_1_NoDest)
{
    std::string source =
        "M-1;JNE\n";
    std::istringstream input(source);
    Parser parser(input);
    parser.advance();
    EXPECT_EQ(parser.dest(), "");
    EXPECT_EQ(parser.comp(), "M-1");
    EXPECT_EQ(parser.jump(), "JNE");
}

TEST(ParserTest, CCommand_2_NoJump)
{
    std::string source =
        "M=D+1\n";
    std::istringstream input(source);
    Parser parser(input);
    parser.advance();
    EXPECT_EQ(parser.dest(), "M");
    EXPECT_EQ(parser.comp(), "D+1");
    EXPECT_EQ(parser.jump(), "");
}

TEST(ParserTest, CCommand_3_OnlyComp)
{
    std::string source =
        "M+1\n";
    std::istringstream input(source);
    Parser parser(input);
    parser.advance();
    EXPECT_EQ(parser.dest(), "");
    EXPECT_EQ(parser.comp(), "M+1");
    EXPECT_EQ(parser.jump(), "");
}

TEST(ParserTest, CCommand_4_WithWhitespace)
{
    std::string source =
        "   D=D+1;JLT   \n";
    std::istringstream input(source);
    Parser parser(input);
    parser.advance();
    EXPECT_EQ(parser.dest(), "D");
    EXPECT_EQ(parser.comp(), "D+1");
    EXPECT_EQ(parser.jump(), "JLT");
}

TEST(ParserTest, CCommand_5_WithComment)
{
    std::string source =
        "D=D+1;JLT // This is a comment\n";
    std::istringstream input(source);
    Parser parser(input);
    parser.advance();
    EXPECT_EQ(parser.dest(), "D");
    EXPECT_EQ(parser.comp(), "D+1");
    EXPECT_EQ(parser.jump(), "JLT");
}

TEST(ParserTest, CCommand_6_WithWhitespaceAndComment)
{
    std::string source =
        "   D=D+1;JLT   // This is a comment\n";
    std::istringstream input(source);
    Parser parser(input);
    parser.advance();
    EXPECT_EQ(parser.dest(), "D");
    EXPECT_EQ(parser.comp(), "D+1");
    EXPECT_EQ(parser.jump(), "JLT");
}

TEST(ParserTest, Complex_0)
{
    std::string source =
        "   // This is a comment\n"
        "@2 // This is a comment\n"
        "M=D // Another comment\n"
        "(LOOP) // Yet another comment\n"
        "D=D+1;JLT // Final comment\n";
    std::istringstream input(source);
    Parser parser(input);

    EXPECT_TRUE(parser.hasMoreCommands());
    parser.advance();
    EXPECT_EQ(parser.commandType(), CommandType::A_COMMAND);
    EXPECT_EQ(parser.symbol(), "2");

    EXPECT_TRUE(parser.hasMoreCommands());
    parser.advance();
    EXPECT_EQ(parser.commandType(), CommandType::C_COMMAND);
    EXPECT_EQ(parser.dest(), "M");
    EXPECT_EQ(parser.comp(), "D");
    EXPECT_EQ(parser.jump(), "");

    EXPECT_TRUE(parser.hasMoreCommands());
    parser.advance();
    EXPECT_EQ(parser.commandType(), CommandType::L_COMMAND);
    EXPECT_EQ(parser.symbol(), "LOOP");

    EXPECT_TRUE(parser.hasMoreCommands());
    parser.advance();
    EXPECT_EQ(parser.commandType(), CommandType::C_COMMAND);
    EXPECT_EQ(parser.dest(), "D");
    EXPECT_EQ(parser.comp(), "D+1");
    EXPECT_EQ(parser.jump(), "JLT");

    EXPECT_FALSE(parser.hasMoreCommands());
}

TEST(ParserTest, Complex_1)
{
    std::string source =
        "// This is a comment\n"
        "\n"
        "@2 // This is a comment\n"
        "// Another comment\n"
        "(LOOP) // Yet another comment\n"
        "D=D+1;JEQ // Final comment\n";
    std::istringstream input(source);
    Parser parser(input);

    EXPECT_TRUE(parser.hasMoreCommands());
    parser.advance();
    EXPECT_EQ(parser.commandType(), CommandType::A_COMMAND);
    EXPECT_EQ(parser.symbol(), "2");

    EXPECT_TRUE(parser.hasMoreCommands());
    parser.advance();
    EXPECT_EQ(parser.commandType(), CommandType::L_COMMAND);
    EXPECT_EQ(parser.symbol(), "LOOP");

    EXPECT_TRUE(parser.hasMoreCommands());
    parser.advance();
    EXPECT_EQ(parser.commandType(), CommandType::C_COMMAND);
    EXPECT_EQ(parser.dest(), "D");
    EXPECT_EQ(parser.comp(), "D+1");
    EXPECT_EQ(parser.jump(), "JEQ");

    EXPECT_FALSE(parser.hasMoreCommands());
}
