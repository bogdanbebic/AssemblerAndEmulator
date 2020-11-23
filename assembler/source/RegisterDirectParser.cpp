#include "RegisterDirectParser.hpp"

statement::operand_t parsers::RegisterDirectParser::parse(std::string operand)
{
    if (!this->can_parse(operand))
        return OperandParser::parse(operand);
    return {};
}

bool parsers::RegisterDirectParser::can_parse(std::string operand)
{
    return false;
}
