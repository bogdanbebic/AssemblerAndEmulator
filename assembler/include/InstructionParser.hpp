#ifndef _INSTRUCTION_PARSER_HPP_
#define _INSTRUCTION_PARSER_HPP_

#include "StatementParser.hpp"

#include <memory>

#include "ObjectCodeArray.hpp"
#include "SymbolTable.hpp"

namespace parsers
{
    class InstructionParser : public StatementParser
    {
    public:
        explicit InstructionParser(std::shared_ptr<assembler::SymbolTable> symbol_table,
                                   std::shared_ptr<assembler::ObjectCodeArray> object_code);

        std::shared_ptr<statements::Statement> parse(std::string statement) override;

    private:
        bool can_parse(const std::string &statement) const;

        std::shared_ptr<assembler::SymbolTable> symbol_table_;
        std::shared_ptr<assembler::ObjectCodeArray> object_code_;
    };
} // namespace parsers

#endif
