#ifndef _MEMORY_DIRECT_PARSER_HPP_
#define _MEMORY_DIRECT_PARSER_HPP_

#include "OperandParser.hpp"

namespace assembler
{
    class SymbolTable;
} // namespace assembler

namespace parsers
{
    class MemoryDirectParser : public OperandParser
    {
    public:
        std::shared_ptr<statement::operand_t> parse(std::string operand);
        std::shared_ptr<statement::operand_t> parse_jump_instruction(std::string operand);

        explicit MemoryDirectParser(std::shared_ptr<assembler::SymbolTable> symbol_table);

    private:
        bool can_parse(const std::string &operand) const;
        bool can_parse_jump_instruction(const std::string &operand) const;

        void add_memory_direct_relocation(std::string symbol,
                                          std::shared_ptr<statement::operand_t> operand);

        std::shared_ptr<assembler::SymbolTable> symbol_table_;
    };
} // namespace parsers

#endif
