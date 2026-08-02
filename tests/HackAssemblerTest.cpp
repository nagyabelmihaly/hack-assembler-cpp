#include <filesystem>
#include <fstream>
#include <sstream>
#include <vector>

#include <gtest/gtest.h>

#include "HackAssembler.hpp"

namespace fs = std::filesystem;

namespace
{

std::string readFile(const fs::path &path)
{
    std::ifstream file(path);
    std::ostringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}

std::vector<fs::path> discoverAsmFixtures()
{
    std::vector<fs::path> result;
    for (const auto &entry : fs::directory_iterator(fs::path(FIXTURES_DIR)))
    {
        if (entry.path().extension() == ".asm")
        {
            result.push_back(entry.path());
        }
    }
    return result;
}

}  /* namespace */

class HackAssemblerTest : public ::testing::TestWithParam<fs::path>
{
};

TEST_P(HackAssemblerTest, MatchesReferenceOutput)
{
    const fs::path& asmPath = GetParam();
    fs::path expectedPath = asmPath;
    expectedPath.replace_extension(".hack");

    fs::path actualPath = fs::temp_directory_path() / (asmPath.stem().string() + "_actual.hack");

    InputPath inputPath{asmPath.string()};
    OutputPath outputPath{actualPath.string()};

    HackAssembler assembler(inputPath, outputPath);
    assembler.assemble();

    std::string expected = readFile(expectedPath);
    std::string actual = readFile(actualPath);

    EXPECT_TRUE(actual == expected) << "Mismatch for: " << asmPath.filename();

    fs::remove(actualPath);   // clean up the temp file after comparing
}

INSTANTIATE_TEST_SUITE_P(
    AllFixtures,
    HackAssemblerTest,
    ::testing::ValuesIn(discoverAsmFixtures()),
    [](const ::testing::TestParamInfo<fs::path> &info)
    {
        return info.param.stem().string();   // test name = file stem, e.g. "Add", "MaxL"
    }
);