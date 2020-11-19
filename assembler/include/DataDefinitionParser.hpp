#ifndef DATA_DEFINITION_PARSER_H_GUARD
#define DATA_DEFINITION_PARSER_H_GUARD

#include "StatementParser.hpp"

#include <memory>

#include "ObjectCodeArray.hpp"
#include "SymbolTable.hpp"

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
