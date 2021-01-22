#include "EquDirectiveParser.hpp"

#include <regex>
#include <vector>

#include "ExpressionParser.hpp"
#include "SectionTable.hpp"
#include "SymbolTable.hpp"

parsers::EquDirectiveParser::EquDirectiveParser(std::shared_ptr<assembler::SectionTable> section_table,
                                                std::shared_ptr<assembler::SymbolTable> symbol_table)
    : section_table_(std::move(section_table)), symbol_table_(std::move(symbol_table))
{
    // empty body
}

std::shared_ptr<statements::Statement> parsers::EquDirectiveParser::parse(std::string statement)
{
    if (!this->can_parse(statement))
        return StatementParser::parse(statement);

    const std::regex regex{ "^\\.equ\\s+(\\w+),(.+)$" };
    std::smatch match;
    if (std::regex_match(statement, match, regex))
    {
        auto symbol     = match[1].str();
        auto expression = match[2].str();
        auto value = ExpressionParser::evaluate_expression(expression, this->symbol_table_);

        auto relocation_symbol = this->get_relocation_symbol(expression);

        this->symbol_table_->insert({ symbol, { symbol, value, 1, false } });
    }

    return nullptr;
}

bool parsers::EquDirectiveParser::can_parse(const std::string &statement) const
{
    const std::regex regex{ "^\\.(equ)\\s+.*$" };
    return std::regex_match(statement, regex);
}

std::string parsers::EquDirectiveParser::get_relocation_symbol(std::string expression) const
{
    std::vector<int> classification_index(this->section_table_->size());
    std::vector<std::string> relocation_symbols(this->section_table_->size());

    expression.erase(std::remove_if(expression.begin(),
                                    expression.end(),
                                    [](int ch) { return std::isspace(ch); }),
                     expression.end());

    if (expression[0] != '+' && expression[0] != '-')
    {
        expression = '+' + expression;
    }

    const std::regex regex("[\\+-]\\w+");
    std::smatch match;
    while (std::regex_search(expression, match, regex))
    {
        std::string operand = match.str();
        if (!ExpressionParser::is_literal(operand))
        {
            const size_t section_table_idx =
                this->symbol_table_->at(operand.substr(1)).section_index;
            classification_index[section_table_idx] +=
                (operand[0] == '-' && section_table_idx != 0 ? -1 : 1);
            relocation_symbols[section_table_idx] = operand.substr(1);
        }

        expression = match.suffix();
    }

    std::string ret;
    bool is_one = false;
    size_t i    = 0;
    for (auto &elem : classification_index)
    {
        if (elem == 1)
        {
            if (is_one)
            {
                throw std::invalid_argument{ "EQU expression invalid" };
            }
            else
            {
                is_one = true;
                ret    = relocation_symbols[i];
            }
        }
        else if (elem != 0)
        {
            throw std::invalid_argument{ "EQU expression invalid" };
        }

        i++;
    }

    return ret;
}
