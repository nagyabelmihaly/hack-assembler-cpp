#pragma once

#include <stdexcept>
#include <string>

class Code
{
public:
    /**
     * Returns the destination bits for the given mnemonic.
     *
     * @param mnemonic The mnemonic to translate into destination bits.
     * @return A 3-bit string representing the destination field.
     */
    static std::string dest(const std::string& mnemonic);
};
