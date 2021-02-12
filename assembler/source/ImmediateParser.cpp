#include "ImmediateParser.hpp"

#include "ExpressionParser.hpp"
#include "RelocationTable.hpp"
#include "SymbolTable.hpp"

std::shared_ptr<statement::operand_t> parsers::ImmediateParser::parse(std::string operand)
{
    if (!this->can_parse(operand))
        return OperandParser::parse(operand);

    auto ret             = std::make_shared<statement::operand_t>();
    ret->addressing_mode = statement::IMMEDIATE;

    auto operand_stripped = operand.substr(1);
    auto value = ExpressionParser::evaluate_expression(operand_stripped, this->symbol_table_);

    if (this->symbol_table_->is_global(operand_stripped))
        value = 0;

    ret->operand[0] = static_cast<uint8_t>(value & 0x00FF);
    ret->operand[1] = static_cast<uint8_t>((value & 0xFF00) >> 8);

    if (!ExpressionParser::is_literal(operand_stripped))
        this->add_immediate_relocation(operand_stripped, ret);

    return ret;
}

std::shared_ptr<statement::operand_t>
parsers::ImmediateParser::parse_jump_instruction(std::string operand)
{
    if (!this->can_parse_jump_instruction(operand))
        return OperandParser::parse_jump_instruction(operand);

    auto ret             = std::make_shared<statement::operand_t>();
    ret->addressing_mode = statement::IMMEDIATE;

    auto value = ExpressionParser::evaluate_expression(operand, this->symbol_table_);

    if (this->symbol_table_->is_global(operand))
        value = 0;

    ret->operand[0] = static_cast<uint8_t>(value & 0x00FF);
    ret->operand[1] = static_cast<uint8_t>((value & 0xFF00) >> 8);

    if (!ExpressionParser::is_literal(operand))
        this->add_immediate_relocation(operand, ret);

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

void parsers::ImmediateParser::add_immediate_relocation(std::string symbol,
                                                        std::shared_ptr<statement::operand_t> operand)
{
    auto relocation_type = this->symbol_table_->is_defined(symbol) &&
                                   !this->symbol_table_->is_global(symbol)
                               ? assembler::RelocationTable::R_SECTION16
                               : assembler::RelocationTable::R_16;
    operand->relocation = std::make_shared<assembler::RelocationTable::relocation_table_entry_t>(
        assembler::RelocationTable::relocation_table_entry_t{ symbol, relocation_type });
}
