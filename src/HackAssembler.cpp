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
}

} // namespace hack
