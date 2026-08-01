#include "Code.hpp"

std::string Code::dest(const std::string& mnemonic)
{
    if (mnemonic.empty())
    {
        return "000";
    }
    else if (mnemonic == "M")
    {
        return "001";
    }
    else if (mnemonic == "D")
    {
        return "010";
    }
    else if (mnemonic == "MD")
    {
        return "011";
    }
    else if (mnemonic == "A")
    {
        return "100";
    }
    else if (mnemonic == "AM")
    {
        return "101";
    }
    else if (mnemonic == "AD")
    {
        return "110";
    }
    else if (mnemonic == "AMD")
    {
        return "111";
    }
    else
    {
        throw std::invalid_argument("Invalid destination mnemonic: " + mnemonic);
    }
}
