#ifndef _REGISTER_INDIRECT_OFFSET_PARSER_HPP_
#define _REGISRER_INDRIECT_OFFSET_PARSER_HPP_

#include "OperandParser.hpp"

#include "SymbolTable.hpp"

namespace parsers
{
    class RegisterIndirectOffsetParser : public OperandParser
    {
    public:
        std::shared_ptr<statement::operand_t> parse(std::string operand);
        std::shared_ptr<statement::operand_t> parse_jump_instruction(std::string operand);

        explicit RegisterIndirectOffsetParser(std::shared_ptr<assembler::SymbolTable> symbol_table);

    private:
        bool can_parse(const std::string &operand) const;
        bool can_parse_jump_instruction(const std::string &operand) const;

        std::shared_ptr<assembler::SymbolTable> symbol_table_;
    };
} // namespace parsers

#endif