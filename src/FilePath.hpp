#pragma once

#include <string>

namespace hack
{

/**
 * Represents the path to an input file.
 */
struct InputPath
{
    /** The path to the input file. */
    std::string path;
};

/**
 * Represents the path to an output file.
 */
struct OutputPath
{
    /** The path to the output file. */
    std::string path;
};

} // namespace hack
