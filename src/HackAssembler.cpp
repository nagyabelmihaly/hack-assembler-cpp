#include <format>
#include <fstream>
#include <iostream>
#include <string>

#include "HackAssembler.hpp"
#include "Code.hpp"
#include "CommandType.hpp"
#include "FilePath.hpp"
#include "Parser.hpp"

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
