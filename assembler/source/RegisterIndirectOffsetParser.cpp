#include "RegisterIndirectOffsetParser.hpp"

#include <regex>

#include "ExpressionParser.hpp"
#include "SymbolTable.hpp"

std::shared_ptr<statement::operand_t> parsers::RegisterIndirectOffsetParser::parse(std::string operand)
{
    if (!this->can_parse(operand))
        return OperandParser::parse(operand);

    auto ret             = std::make_shared<statement::operand_t>();
    ret->addressing_mode = statement::REGISTER_INDIRECT_OFFSET;

    const std::regex register_indirect_offset_regex{ "^([_a-zA-Z0-9]+)\\(%(r[0-7]|pc|sp|psw)([hl]?)\\)$" };
    std::smatch match;

    if (std::regex_match(operand, match, register_indirect_offset_regex))
    {
        auto operand_offset = match[1].str();
        auto base_register  = match[2].str();
        auto low_high_byte  = match[3].str();
        if (low_high_byte.size() == 1)
        {
            ret->low_high_byte_exists = 1;
            if (low_high_byte == "h")
                ret->low_high_byte = 1;
        }

        const std::regex regex_base_reg{ "^r([0-7])$" };
        std::smatch match_base_reg;

        if (std::regex_match(base_register, match_base_reg, regex_base_reg))
            ret->register_index = std::stoi(match_base_reg[1].str());
        else if (base_register == "pc")
            ret->register_index = 7;
        else if (base_register == "sp")
            ret->register_index = 6;
        else if (base_register == "psw")
            ret->register_index = 0xF;

        auto offset_value =
            ExpressionParser::evaluate_expression(operand_offset, this->symbol_table_);

        if (this->symbol_table_->is_global(operand_offset))
            offset_value = 0;

        ret->operand[0] = static_cast<uint8_t>(offset_value & 0x00FF);
        ret->operand[1] = static_cast<uint8_t>((offset_value & 0xFF00) >> 8);

        if (!ExpressionParser::is_literal(operand_offset))
        {
            if (base_register == "pc" || base_register == "r7")
                add_pc_relative_relocation(operand_offset, ret);
            else
                add_register_relative_relocation(operand_offset, ret);
        }
    }
    else
    {
        // should never happen
        return nullptr;
    }

    return ret;
}

std::shared_ptr<statement::operand_t>
parsers::RegisterIndirectOffsetParser::parse_jump_instruction(std::string operand)
{
    if (!this->can_parse_jump_instruction(operand))
        return OperandParser::parse_jump_instruction(operand);

    auto ret             = std::make_shared<statement::operand_t>();
    ret->addressing_mode = statement::REGISTER_INDIRECT_OFFSET;

    const std::regex register_indirect_offset_regex{ "^\\*([_a-zA-Z0-9]+)\\(%(r[0-7]|pc|sp|psw)([hl]?)\\)$" };
    std::smatch match;

    if (std::regex_match(operand, match, register_indirect_offset_regex))
    {
        auto operand_offset = match[1].str();
        auto base_register  = match[2].str();
        auto low_high_byte  = match[3].str();
        if (low_high_byte.size() == 1)
        {
            ret->low_high_byte_exists = 1;
            if (low_high_byte == "h")
                ret->low_high_byte = 1;
        }

        const std::regex regex_base_reg{ "^r([0-7])$" };
        std::smatch match_base_reg;

        if (std::regex_match(base_register, match_base_reg, regex_base_reg))
            ret->register_index = std::stoi(match_base_reg[1].str());
        else if (base_register == "pc")
            ret->register_index = 7;
        else if (base_register == "sp")
            ret->register_index = 6;
        else if (base_register == "psw")
            ret->register_index = 0xF;

        auto offset_value =
            ExpressionParser::evaluate_expression(operand_offset, this->symbol_table_);

        if (this->symbol_table_->is_global(operand_offset))
            offset_value = 0;

        ret->operand[0] = static_cast<uint8_t>(offset_value & 0x00FF);
        ret->operand[1] = static_cast<uint8_t>((offset_value & 0xFF00) >> 8);

        if (!ExpressionParser::is_literal(operand_offset))
        {
            if (base_register == "pc" || base_register == "r7")
                add_pc_relative_relocation(operand_offset, ret);
            else
                add_register_relative_relocation(operand_offset, ret);
        }
    }
    else
    {
        // should never happen
        return nullptr;
    }

    return ret;
}

parsers::RegisterIndirectOffsetParser::RegisterIndirectOffsetParser(
    std::shared_ptr<assembler::SymbolTable> symbol_table)
    : symbol_table_(std::move(symbol_table))
{
    // empty body
}

bool parsers::RegisterIndirectOffsetParser::can_parse(const std::string &operand) const
{
    const std::regex register_indirect_offset_regex{ "^[_a-zA-Z0-9]+\\(%(r[0-7]|pc|sp|psw)([hl]?)\\)$" };
    return std::regex_match(operand, register_indirect_offset_regex);
}

bool parsers::RegisterIndirectOffsetParser::can_parse_jump_instruction(const std::string &operand) const
{
    const std::regex register_indirect_offset_regex{ "^\\*[_a-zA-Z0-9]+\\(%(r[0-7]|pc|sp|psw)([hl]?)\\)$" };
    return std::regex_match(operand, register_indirect_offset_regex);
}

void parsers::RegisterIndirectOffsetParser::add_pc_relative_relocation(
    std::string symbol, std::shared_ptr<statement::operand_t> operand)
{
    if (!this->symbol_table_->is_defined(symbol) || this->symbol_table_->is_global(symbol))
    {
        operand->relocation = std::make_shared<assembler::RelocationTable::relocation_table_entry_t>(
            assembler::RelocationTable::relocation_table_entry_t{
                symbol, assembler::RelocationTable::R_PC16 });
    }
}

void parsers::RegisterIndirectOffsetParser::add_register_relative_relocation(
    std::string symbol, std::shared_ptr<statement::operand_t> operand)
{
    auto relocation_type = this->symbol_table_->is_defined(symbol) &&
                                   !this->symbol_table_->is_global(symbol)
                               ? assembler::RelocationTable::R_SECTION16
                               : assembler::RelocationTable::R_16;
    operand->relocation = std::make_shared<assembler::RelocationTable::relocation_table_entry_t>(
        assembler::RelocationTable::relocation_table_entry_t{ symbol, relocation_type });
}
