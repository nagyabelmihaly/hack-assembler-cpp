#include "SymbolTable.hpp"

#include <stdexcept>

namespace hack
{

SymbolTable::SymbolTable() = default;

void SymbolTable::addEntry(const std::string& symbol, int address)
{
    symbolTable_[symbol] = address;
}

bool SymbolTable::contains(const std::string& symbol) const
{
    return symbolTable_.contains(symbol);
}

int SymbolTable::getAddress(const std::string& symbol) const
{
    auto iter = symbolTable_.find(symbol);
    if (iter != symbolTable_.end())
    {
        return iter->second;
    }
    throw std::runtime_error("Symbol not found.");
}

} // namespace hack
