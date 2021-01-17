#ifndef _EQU_DIRECTIVE_PARSER_HPP_
#define _EQU_DIRECTIVE_PARSER_HPP_

#include "StatementParser.hpp"

namespace assembler
{
    class SymbolTable;
} // namespace assembler

namespace parsers
{
    class EquDirectiveParser : public StatementParser
    {
    public:
        explicit EquDirectiveParser(std::shared_ptr<assembler::SymbolTable> symbol_table);
        std::shared_ptr<statements::Statement> parse(std::string statement) override;

    private:
        bool can_parse(const std::string &statement) const;

        std::shared_ptr<assembler::SymbolTable> symbol_table_;
    };
} // namespace parsers

#endif
