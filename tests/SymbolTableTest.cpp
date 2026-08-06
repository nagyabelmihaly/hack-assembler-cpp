#include <gtest/gtest.h>

#include "SymbolTable.hpp"

TEST(SymbolTableTest, SymbolTable_0_NoEntry)
{
    hack::SymbolTable symbolTable;
    EXPECT_FALSE(symbolTable.contains("LOOP"));
}

TEST(SymbolTableTest, SymbolTable_1_AddSingleEntry)
{
    hack::SymbolTable symbolTable;
    symbolTable.addEntry("LOOP", 3);
    EXPECT_TRUE(symbolTable.contains("LOOP"));
    EXPECT_EQ(symbolTable.getAddress("LOOP"), 3);
    EXPECT_FALSE(symbolTable.contains("END"));
}

TEST(SymbolTableTest, SymbolTable_2_AddMultipleEntries)
{
    hack::SymbolTable symbolTable;
    symbolTable.addEntry("LOOP", 2);
    symbolTable.addEntry("END", 4);
    EXPECT_TRUE(symbolTable.contains("LOOP"));
    EXPECT_TRUE(symbolTable.contains("END"));
    EXPECT_EQ(symbolTable.getAddress("LOOP"), 2);
    EXPECT_EQ(symbolTable.getAddress("END"), 4);
    EXPECT_FALSE(symbolTable.contains("START"));
}
