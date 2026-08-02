#include <format>
#include <fstream>
#include <iostream>
#include <string>

#include "HackAssembler.hpp"
#include "Code.hpp"
#include "CommandType.hpp"
#include "FilePath.hpp"
#include "Parser.hpp"

namespace
{
/** The number of bits in an A-command except the leading '0'. */
constexpr size_t A_COMMAND_BITS = 15;

/**
 * Pads the given string on the left with the specified fill character until it reaches the desired total length.
 * 
 * @param str The string to pad.
 * @param totalLength The desired total length of the resulting string.
 * @param fillChar The character to use for padding. Defaults to '0'.
 * @return A new string that is left-padded to the specified total length.
 */
std::string padLeft(const std::string& str, size_t totalLength, char fillChar = '0')
{
    if (str.length() >= totalLength)
    {
        return str;
    }
    return std::string(totalLength - str.length(), fillChar) + str;
}
} /* namespace */

HackAssembler::HackAssembler(const InputPath &inputPath, const OutputPath &outputPath)
    : inputPath_(inputPath.path), outputPath_(outputPath.path)
{
    /* No actions to take */
}

void HackAssembler::assemble()
{
    std::ifstream inputFile(inputPath_);
    if (!inputFile.is_open())
    {
        std::cerr << "Error: Could not open input file: " << inputPath_ << '\n';
        return;
    }

    std::ofstream outputFile(outputPath_);
    if (!outputFile.is_open())
    {
        std::cerr << "Error: Could not open output file: " << outputPath_ << '\n';
        return;
    }

    Parser parser(inputFile);

    while (parser.hasMoreCommands())
    {
        parser.advance();

        std::string symbol;
        std::string dest;
        std::string comp;
        std::string jump;

        switch (parser.commandType())
        {
        case CommandType::A_COMMAND:
            // Assume the symbol is a decimal number for now, todo: handle symbols
            symbol = parser.symbol();
             // Convert to binary and pad to 15 bits
            outputFile << "0" << std::format("{:015b}", std::stoi(symbol)) << '\n';
            break;
        case CommandType::C_COMMAND:            
            dest = Code::dest(parser.dest());
            comp = Code::comp(parser.comp());
            jump = Code::jump(parser.jump());
            outputFile << "111" << comp << dest << jump << '\n';
            break;
        case CommandType::L_COMMAND:
            // Handle L-command parsing, todo
            break;
        default:
            std::cerr << "Error: Unknown command type encountered.\n";
            break;
        }
    }
}
