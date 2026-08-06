#include <filesystem>
#include <iostream>
#include <string_view>

#include "HackAssembler.hpp"

namespace fs = std::filesystem;

constexpr int kMainErrorUsage = 1;
constexpr int kMainErrorPath = 2;
constexpr int kMainErrorFilesystem = 3;
constexpr int kMainErrorIO = 4;
constexpr int kMainErrorMemory = 5;
constexpr int kMainErrorException = 6;

int main(int argc, char *argv[])
{
    constexpr std::string_view msg = "Hack Assembler C++20 - v0.1 (symbol-less version)";
    std::cout << msg << '\n';

    try
    {
        if (argc != 2)
        {
            std::cerr << "Usage: " << argv[0] << " <input.asm>\n";
            return kMainErrorUsage;
        }

        std::string inputStr = argv[1];

        std::error_code errorCode;
        fs::path inputResolved = fs::canonical(inputStr, errorCode);
        if (errorCode)
        {
            std::cerr << "Error resolving path " << inputStr << ": " << errorCode.message() << "\n";
            return kMainErrorPath;
        }

        fs::path outputResolved = inputResolved;
        outputResolved.replace_extension(".hack");

        hack::InputPath inputPath{inputResolved.string()};
        hack::OutputPath outputPath{outputResolved.string()};

        hack::HackAssembler assembler(inputPath, outputPath);

        std::cout << "Assembling " << inputResolved << "\n";

        assembler.assemble();

        std::cout << "Assembled to " << outputResolved << "\n";

        return 0;
    }
    catch (const std::filesystem::filesystem_error& error)
    {
        std::cerr << "Filesystem error: " << error.what() << "\n";
        return kMainErrorFilesystem;
    }
    catch (const std::ios_base::failure& error)
    {
        std::cerr << "I/O error: " << error.what() << "\n";
        return kMainErrorIO;
    }
    catch (const std::bad_alloc& error)
    {
        std::cerr << "Out of memory: " << error.what() << "\n";
        return kMainErrorMemory;
    }
    catch (const std::exception& error)
    {
        std::cerr << "Error: " << error.what() << "\n";
        return kMainErrorException;
    }
}
