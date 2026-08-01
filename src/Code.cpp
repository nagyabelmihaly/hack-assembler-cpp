#include <stdexcept>

#include "Code.hpp"

std::string Code::dest(const std::string& mnemonic)
{
    std::string destBits;
    if (mnemonic.empty())
    {
        destBits = "000";
    }
    else if (mnemonic == "M")
    {
        destBits = "001";
    }
    else if (mnemonic == "D")
    {
        destBits = "010";
    }
    else if (mnemonic == "MD")
    {
        destBits = "011";
    }
    else if (mnemonic == "A")
    {
        destBits = "100";
    }
    else if (mnemonic == "AM")
    {
        destBits = "101";
    }
    else if (mnemonic == "AD")
    {
        destBits = "110";
    }
    else if (mnemonic == "AMD")
    {
        destBits = "111";
    }
    else
    {
        throw std::invalid_argument("Invalid destination mnemonic: " + mnemonic);
    }
    return destBits;
}
