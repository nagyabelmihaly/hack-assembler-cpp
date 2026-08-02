#include "HackAssembler.hpp"

HackAssembler::HackAssembler(const InputPath &inputPath, const OutputPath &outputPath)
    : inputPath_(inputPath.path), outputPath_(outputPath.path)
{
    /* No actions to take */
}

void HackAssembler::assemble()
{
    // Implementation of the assemble method goes here.
    // This method should read the input .asm file, parse it, and write the output .hack file.
}
