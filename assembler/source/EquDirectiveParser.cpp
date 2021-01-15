#include "EquDirectiveParser.hpp"

#include <regex>

parsers::EquDirectiveParser::EquDirectiveParser(std::shared_ptr<assembler::SymbolTable> symbol_table)
    : symbol_table_(std::move(symbol_table))
{
    // empty body
}

std::shared_ptr<statements::Statement> parsers::EquDirectiveParser::parse(std::string statement)
{
    if (!this->can_parse(statement))
        return StatementParser::parse(statement);

    // TODO: implement
    return nullptr;
}

bool parsers::EquDirectiveParser::can_parse(const std::string &statement) const
{
    const std::regex regex{ "^\\.(equ)\\s+.*$" };
    return std::regex_match(statement, regex);
}
