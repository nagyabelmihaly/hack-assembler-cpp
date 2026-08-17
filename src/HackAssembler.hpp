#pragma once

#include <string>
#include <fstream>

#include "FilePath.hpp"
#include "Parser.hpp"
#include "SymbolTable.hpp"

namespace hack
{

/**
 * The HackAssembler class is responsible for assembling Hack assembly code into binary machine code.
 * It takes an input .asm file and produces an output .hack file.
 */
class HackAssembler
{
public:
    /**
     * Constructs a HackAssembler object with the given input and output file paths.
     *
     * @param inputPath The path to the input .asm file.
     * @param outputPath The path to the output .hack file.
     */
    HackAssembler(const InputPath &inputPath, const OutputPath &outputPath);

    /**
     * Assembles the input .asm file into the output .hack file.
     */
    void assemble();

private:
    void initializeSymbolTable();
    void firstPass(Parser &parser);
    void secondPass(Parser &parser, std::ofstream &outputFile);

    std::string inputPath_;
    std::string outputPath_;
    SymbolTable symbolTable_;
};

} // namespace hack
