#pragma once

#include <string>

#include "FilePath.hpp"

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
    std::string inputPath_;
    std::string outputPath_;
};
