#pragma once

#include <cstdint>

namespace hack
{

/**
 * Represents the type of a command in the Hack assembly language.
 */
enum class CommandType : std::uint8_t
{
    A_COMMAND,  // @Xxx where Xxx is either a symbol or a decimal number
    C_COMMAND,  // dest=comp;jump
    L_COMMAND   // (XXX) where XXX is a symbol
};

} // namespace hack
