#pragma once

#include <string>

namespace hack
{

/**
 * The SymbolTable class is responsible for managing the symbol table used in the Hack Assembler.
 * Symbolic strings can be mapped to integers, and then these mappings can be queried.
 */
class SymbolTable
{
public:
    /**
     * Constructs a SymbolTable object with no mappings.
     */
    SymbolTable();

    /**
     * Adds the pair (symbol, address) to the table.
     * 
     * @param symbol The symbolic string to add to the table.
     * @param address The integer address to associate with the symbol.
     */
    void addEntry(const std::string& symbol, int address);

    /**
     * Determines if the symbol table contains the given symbol.
     * 
     * @param symbol The symbolic string to query.
     * @return True if the symbol is in the table, false otherwise.
     */
    [[nodiscard]] bool contains(const std::string& symbol) const;

    /**
     * Returns the address associated with the given symbol.
     * 
     * @param symbol The symbolic string to query.
     * @return The integer address associated with the symbol.
     */
    [[nodiscard]] int getAddress(const std::string& symbol) const;
};

} // namespace hack
