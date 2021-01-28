#ifndef _EQU_DIRECTIVE_PARSER_HPP_
#define _EQU_DIRECTIVE_PARSER_HPP_

#include "StatementParser.hpp"

namespace assembler
{
    class SectionTable;
    class SymbolTable;
    class RelocationTable;
} // namespace assembler

namespace parsers
{
    class EquDirectiveParser : public StatementParser
    {
    public:
        explicit EquDirectiveParser(std::shared_ptr<assembler::SectionTable> section_table,
                                    std::shared_ptr<assembler::SymbolTable> symbol_table,
                                    std::shared_ptr<assembler::RelocationTable> relocation_table);
        std::shared_ptr<statements::Statement> parse(std::string statement) override;

    private:
        bool can_parse(const std::string &statement) const;
        std::string get_relocation_symbol(std::string expression) const;

        std::shared_ptr<assembler::SectionTable> section_table_;
        std::shared_ptr<assembler::SymbolTable> symbol_table_;
        std::shared_ptr<assembler::RelocationTable> relocation_table_;
    };
} // namespace parsers

#endif
