#ifndef _DATA_DEFINITION_PARSER_HPP_
#define _DATA_DEFINITION_PARSER_HPP_

#include "StatementParser.hpp"

#include <memory>

namespace assembler
{
    class ObjectCodeArray;
    class SymbolTable;
} // namespace assembler

namespace parsers
{
    class DataDefinitionParser : public StatementParser
    {
    public:
        explicit DataDefinitionParser(std::shared_ptr<assembler::ObjectCodeArray> object_code,
                                      std::shared_ptr<assembler::SymbolTable> symbol_table);
        std::shared_ptr<statements::Statement> parse(std::string statement) override;

    private:
        bool can_parse(const std::string &statement) const;

        std::shared_ptr<assembler::ObjectCodeArray> object_code_;
        std::shared_ptr<assembler::SymbolTable> symbol_table_;
    };
} // namespace parsers

#endif
