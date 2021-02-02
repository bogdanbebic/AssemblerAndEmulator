#ifndef _DATA_DEFINITION_PARSER_HPP_
#define _DATA_DEFINITION_PARSER_HPP_

#include "StatementParser.hpp"

#include <memory>

namespace assembler
{
    class ObjectCodeArray;
    class SymbolTable;
    class RelocationTable;
} // namespace assembler

namespace parsers
{
    class DataDefinitionParser : public StatementParser
    {
    public:
        explicit DataDefinitionParser(std::shared_ptr<assembler::ObjectCodeArray> object_code,
                                      std::shared_ptr<assembler::SymbolTable> symbol_table,
                                      std::shared_ptr<assembler::RelocationTable> relocation_table);
        std::shared_ptr<statements::Statement> parse(std::string statement) override;

    private:
        bool can_parse(const std::string &statement) const;

        void add_byte_relocation(std::string symbol);
        void add_word_relocation(std::string symbol);

        std::shared_ptr<assembler::ObjectCodeArray> object_code_;
        std::shared_ptr<assembler::SymbolTable> symbol_table_;
        std::shared_ptr<assembler::RelocationTable> relocation_table_;
    };
} // namespace parsers

#endif
