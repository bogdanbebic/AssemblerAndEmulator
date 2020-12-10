#include "ImmediateParser.hpp"

#include "LiteralParser.hpp"

std::shared_ptr<statement::operand_t> parsers::ImmediateParser::parse(std::string operand)
{
    if (!this->can_parse(operand))
        return OperandParser::parse(operand);

    auto ret             = std::make_shared<statement::operand_t>();
    ret->addressing_mode = statement::IMMEDIATE;

    auto operand_stripped = operand.substr(1);
    auto value = LiteralParser::evaluate_expression(operand_stripped, this->symbol_table_);
    ret->operand[0] = static_cast<uint8_t>(value & 0x00FF);
    ret->operand[1] = static_cast<uint8_t>((value & 0xFF00) >> 8);

    return ret;
}

std::shared_ptr<statement::operand_t>
parsers::ImmediateParser::parse_jump_instruction(std::string operand)
{
    if (!this->can_parse_jump_instruction(operand))
        return OperandParser::parse_jump_instruction(operand);

    auto ret             = std::make_shared<statement::operand_t>();
    ret->addressing_mode = statement::IMMEDIATE;

    auto value = LiteralParser::evaluate_expression(operand, this->symbol_table_);
    ret->operand[0] = static_cast<uint8_t>(value & 0x00FF);
    ret->operand[1] = static_cast<uint8_t>((value & 0xFF00) >> 8);

    return ret;
}

parsers::ImmediateParser::ImmediateParser(std::shared_ptr<assembler::SymbolTable> symbol_table)
    : symbol_table_(std::move(symbol_table))
{
    // empty body
}

bool parsers::ImmediateParser::can_parse(const std::string &operand) const
{
    const std::regex regex{ "^\\$[_a-zA-Z0-9]+$" };
    return std::regex_match(operand, regex);
}

bool parsers::ImmediateParser::can_parse_jump_instruction(const std::string &operand) const
{
    const std::regex regex{ "^[_a-zA-Z0-9]+$" };
    return std::regex_match(operand, regex);
}
