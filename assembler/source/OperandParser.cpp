#include "OperandParser.hpp"

#include <utility>

std::shared_ptr<statement::operand_t> parsers::OperandParser::parse(std::string operand)
{
    if (this->next_ != nullptr)
    {
        return this->next_->parse(std::move(operand));
    }

    return nullptr;
}

std::shared_ptr<statement::operand_t> parsers::OperandParser::parse_jump_instruction(std::string operand)
{
    if (this->next_ != nullptr)
    {
        return this->next_->parse(std::move(operand));
    }

    return nullptr;
}

void parsers::OperandParser::set_next(std::shared_ptr<OperandParser> operand_parser)
{
    this->next_ = std::move(operand_parser);
}
