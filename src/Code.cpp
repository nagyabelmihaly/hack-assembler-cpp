#include <stdexcept>
#include <unordered_map>

#include "Code.hpp"

std::string Code::dest(const std::string& mnemonic)
{
    static const std::unordered_map<std::string, std::string> table
    {
        {"", "000"},
        {"M", "001"},
        {"D", "010"},
        {"MD", "011"},
        {"A", "100"},
        {"AM", "101"},
        {"AD", "110"},
        {"AMD", "111"},
    };

    auto iter = table.find(mnemonic);
    if (iter == table.end())
    {
        throw std::invalid_argument("Invalid destination mnemonic: " + mnemonic);
    }
    return iter->second;
}
