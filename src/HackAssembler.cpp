#include "HackAssembler.hpp"

#include <format>
#include <fstream>
#include <iostream>
#include <string>

#include "Code.hpp"
#include "CommandType.hpp"
#include "FilePath.hpp"
#include "Parser.hpp"

namespace hack
{

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
        throw std::runtime_error("Could not open input file: " + inputPath_);
    }

    std::ofstream outputFile(outputPath_);
    if (!outputFile.is_open())
    {
        throw std::runtime_error("Could not open output file: " + outputPath_);
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

    initializeSymbolTable();
    firstPass();
    secondPass();
}

void HackAssembler::initializeSymbolTable()
{
    symbolTable_ = SymbolTable();

    constexpr std::array<std::pair<std::string_view, int>, 23> predefined
    {{
        {"SP",     0x0000},
        {"LCL",    0x0001},
        {"ARG",    0x0002},
        {"THIS",   0x0003},
        {"THAT",   0x0004},
        {"R0",     0x0000},
        {"R1",     0x0001},
        {"R2",     0x0002},
        {"R3",     0x0003},
        {"R4",     0x0004},
        {"R5",     0x0005},
        {"R6",     0x0006},
        {"R7",     0x0007},
        {"R8",     0x0008},
        {"R9",     0x0009},
        {"R10",    0x000A},
        {"R11",    0x000B},
        {"R12",    0x000C},
        {"R13",    0x000D},
        {"R14",    0x000E},
        {"R15",    0x000F},
        {"SCREEN", 0x4000},
        {"KBD",    0x6000},
    }};

    for (const auto &[name, address] : predefined)
    {
        symbolTable_.addEntry(std::string(name), address);
    }
}

void HackAssembler::firstPass()
{
    // to implement
}

void HackAssembler::secondPass()
{
    // to implement
}

} // namespace hack
