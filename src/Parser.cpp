#include "Parser.hpp"
#include <string_view>

namespace
{
/**
 * Trims leading and trailing whitespace from a string_view.
 *
 * @param str The string_view to trim.
 * @return A new string_view with leading and trailing whitespace removed.
 */
std::string_view trimWhitespace(std::string_view str)
{
    constexpr std::string_view whitespace = " \t\r\n";

    size_t start = str.find_first_not_of(whitespace);
    if (start == std::string_view::npos)
    {
        /* entirely whitespace (or empty) */
        return {};
    }

    size_t end = str.find_last_not_of(whitespace);
    return str.substr(start, end - start + 1);
}

/**
 * Removes comments from a string_view. A comment starts with "//" and continues to the end of the line.
 *
 * @param str The string_view to strip comments from.
 * @return A new string_view with comments removed.
 */
std::string_view stripComment(std::string_view str)
{
    size_t commentPos = str.find("//");
    if (commentPos == std::string_view::npos)
    {
        return str;   // no comment present, unchanged
    }
    return str.substr(0, commentPos);
}
} /* namespace */

Parser::Parser(std::istream& input)
    : input_(&input)
{
    /* No actions to take */
}

bool Parser::hasMoreCommands() const
{
    cacheNextCommand();
    return isNextCommandCached_;
}

void Parser::advance()
{
    if (!hasMoreCommands())
    {
        throw std::runtime_error("No more commands to advance to.");
    }
    currentCommand_ = nextCommand_;
    isNextCommandCached_ = false;
}

CommandType Parser::commandType() const
{
    /* It is assumed that the command is valid */
    if (currentCommand_[0] == '@')
    {
        return CommandType::A_COMMAND;
    }
    if (currentCommand_[0] == '(')
    {
        return CommandType::L_COMMAND;
    }
    return CommandType::C_COMMAND;
}

std::string Parser::symbol() const
{
    /* If command is an A_COMMAND, then trim the @ prefix */
    if (commandType() == CommandType::A_COMMAND)
    {
        return currentCommand_.substr(1);
    }
    /* If command is an L_COMMAND, then trim the ( and ) characters */
    if (commandType() == CommandType::L_COMMAND)
    {
        return currentCommand_.substr(1, currentCommand_.size() - 2);
    }
    throw std::runtime_error("Invalid command type for symbol() call.");
}

std::string Parser::dest() const
{
    if (commandType() != CommandType::C_COMMAND)
    {
        throw std::runtime_error("dest() called on non-C-command.");
    }
    /* If command contains no = then return empty string */
    size_t eqPos = currentCommand_.find('=');
    if (eqPos == std::string_view::npos)
    {
        return "";
    }
    /* Contains = so return what is before it */
    return currentCommand_.substr(0, eqPos);
}

std::string Parser::comp() const
{
    if (commandType() != CommandType::C_COMMAND)
    {
        throw std::runtime_error("comp() called on non-C-command.");
    }
    size_t eqPos = currentCommand_.find('=');
    size_t compStart = 0;
    if (eqPos != std::string_view::npos)
    {
        compStart = eqPos + 1;
    }
    size_t semicolonPos = currentCommand_.find(';');
    size_t compEnd = currentCommand_.size();
    if (compEnd != std::string_view::npos)
    {
        compEnd = semicolonPos;
    }
    return currentCommand_.substr(compStart, compEnd - compStart);
}

std::string Parser::jump() const
{
    if (commandType() != CommandType::C_COMMAND)
    {
        throw std::runtime_error("jump() called on non-C-command.");
    }
    /* If command contains no ; then return empty string */
    size_t semicolonPos = currentCommand_.find(';');
    if (semicolonPos == std::string_view::npos)
    {
        return "";
    }
    /* Contains ; so return what is after it */
    return currentCommand_.substr(semicolonPos + 1, currentCommand_.size() - semicolonPos - 1);
}

void Parser::cacheNextCommand() const
{
    std::string line;

    /* Idempotent behaviour: if cacheNextCommand has been already called
       since the last call to advance(), nothing to cache */
    if (isNextCommandCached_)
    {
        return;
    }

    while (std::getline(*input_, line))
    {
        /* Trim leading/trailing whitespace from the line */
        line = trimWhitespace(line);

        /* If // is found in the line, remove everything after it */
        line = stripComment(line);

        /* Trim whitespace again, as there may be whitespace between command and comment */
        line = trimWhitespace(line);

        /* If the line is empty after trimming, continue to the next line */
        if (line.empty())
        {
            continue;
        }

        /* Otherwise, we have found a valid command; cache it and return */
        nextCommand_ = line;
        isNextCommandCached_ = true;
        return;
    }
}
