#include <iostream>
#include <string_view>

#include "HackAssembler.hpp"

int main(int argc, char *argv[])
{
    constexpr std::string_view msg = "Hack Assembler C++20 - v0.1";
    std::cout << msg << '\n';

    if (argc != 3)
    {
        std::cerr << "Usage: " << argv[0] << " <input.asm> <output.hack>\n";
        return 1;
    }

    InputPath inputPath{argv[1]};
    OutputPath outputPath{argv[2]};

    HackAssembler assembler(inputPath, outputPath);

    std::cout << "Assembling " << inputPath.path << " to " << outputPath.path << "...\n";

    assembler.assemble();

    return 0;
}
