#include "Parser.hpp"

Parser::Parser(std::istream& input)
{
    (void)input;
}

bool Parser::hasMoreCommands() const
{
    return false;
}

void Parser::advance()
{

}

CommandType Parser::commandType() const
{
    return CommandType::A_COMMAND;
}

std::string Parser::symbol() const
{
    return "";
}

std::string Parser::dest() const
{
    return "";
}

std::string Parser::comp() const
{
    return "";
}

std::string Parser::jump() const
{
    return "";
}
