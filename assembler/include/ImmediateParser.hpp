#ifndef _IMMEDIATE_PARSER_HPP_
#define _IMMEDIATE_PARSER_HPP_

#include "OperandParser.hpp"

namespace assembler
{
    class SymbolTable;
} // namespace assembler

namespace parsers
{
    class ImmediateParser final : public OperandParser
    {
    public:
        std::shared_ptr<statement::operand_t> parse(std::string operand) override;
        std::shared_ptr<statement::operand_t> parse_jump_instruction(std::string operand) override;

        explicit ImmediateParser(std::shared_ptr<assembler::SymbolTable> symbol_table);

    private:
        bool can_parse(const std::string &operand) const;
        bool can_parse_jump_instruction(const std::string &operand) const;

        std::shared_ptr<assembler::SymbolTable> symbol_table_;
    };
} // namespace parsers

#endif
