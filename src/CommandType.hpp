#include <cstdint>

enum class CommandType : std::uint8_t
{
    A_COMMAND,  // @Xxx where Xxx is either a symbol or a decimal number
    C_COMMAND,  // dest=comp;jump
    L_COMMAND   // (XXX) where XXX is a symbol
};
