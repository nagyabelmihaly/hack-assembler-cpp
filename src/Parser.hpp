#pragma once

#include <istream>

#include "CommandType.hpp"

namespace hack
{

/**
 * The Parser class is responsible for parsing assembly code from an input stream.
 * It provides methods to read commands, determine their types, and extract relevant components.
 */
class Parser
{
public:
    /**
     * Constructs a Parser object that reads from the given input stream.
     *
     * @param input The input stream to read assembly code from.
     */
    explicit Parser(std::istream& input);

    /**
     * Are there more commands in the input stream?
     *
     * @return True if there is a next command, false otherwise.
     */
    [[nodiscard]] bool hasMoreCommands() const;

    /**
     * Reads the next command from the input stream and makes it the current command.
     * Skips over whitespace and comments if necessary.
     * This method should be called only if hasMoreCommands() is true.
     * Initially, there is no current command.
     */
    void advance();

    /**
     * Returns the type of the current command:
     * A_COMMAND for @Xxx where Xxx is either a symbol or a decimal number
     * C_COMMAND for dest=comp;jump
     * L_COMMAND for (XXX) where XXX is a symbol
     *
     * @return The type of the current command.
     */
    [[nodiscard]] CommandType commandType() const;

    /**
     * If the current command is (XXX), returns the symbol XXX as a string.
     * If the current command is @Xxx, returns the symbol or decimal Xxx as a string.
     * Should be called only when commandType() is A_COMMAND or L_COMMAND.
     *
     * @return The symbol of the current command.
     */
    [[nodiscard]] std::string symbol() const;

    /**
     * Returns the symbolic dest part of the current C-command as a string.
     * Should be called only when commandType() is C_COMMAND.
     *
     * @return The dest part of the current command.
     */
    [[nodiscard]] std::string dest() const;

    /**
     * Returns the symbolic comp part of the current C-command as a string.
     * Should be called only when commandType() is C_COMMAND.
     *
     * @return The comp part of the current command.
     */
    [[nodiscard]] std::string comp() const;

    /**
     * Returns the symbolic jump part of the current C-command as a string.
     * Should be called only when commandType() is C_COMMAND.
     *
     * @return The jump part of the current command.
     */
    [[nodiscard]] std::string jump() const;

private:
    /**
     * Caches the next command from the input stream into nextCommand_,
     * and sets isNextCommandCached_ to true, if there is a next command.
     * If the next command is already cached, does nothing.
     */
    void cacheNextCommand() const;

    // Pointer to the input stream from which assembly code is read.
    std::istream *input_;
    // The current command being processed, for which symbol(), dest(), comp(), and jump() can be called.
    std::string currentCommand_;
    // Cache for the next command to be processed (may or may not contain the next command).
    mutable std::string nextCommand_;
    // Flag indicating whether the next command is cached into nextCommand_ or not.
    mutable bool isNextCommandCached_ = false;
};

} // namespace hack
