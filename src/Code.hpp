#pragma once

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
    [[nodiscard]] static std::string dest(const std::string& mnemonic);
    
    /**
     * Returns the computation bits for the given mnemonic.
     *
     * @param mnemonic The mnemonic to translate into computation bits.
     * @return A 7-bit string representing the computation field.
     */
    [[nodiscard]] static std::string comp(const std::string& mnemonic);
    
    /**
     * Returns the jump bits for the given mnemonic.
     *
     * @param mnemonic The mnemonic to translate into jump bits.
     * @return A 3-bit string representing the jump field.
     */
    [[nodiscard]] static std::string jump(const std::string& mnemonic);
};
