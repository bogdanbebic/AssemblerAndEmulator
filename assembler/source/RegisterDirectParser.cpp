#include "RegisterDirectParser.hpp"

std::shared_ptr<statement::operand_t> parsers::RegisterDirectParser::parse(std::string operand)
{
    if (!this->can_parse(operand))
        return OperandParser::parse(operand);

    // TODO: implement
    return nullptr;
}

bool parsers::RegisterDirectParser::can_parse(std::string operand)
{
    return false;
}
