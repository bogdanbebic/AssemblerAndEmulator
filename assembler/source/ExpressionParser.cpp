#include "ExpressionParser.hpp"

#include <algorithm>
#include <ios>
#include <sstream>

#include "DataDefs.hpp"
#include "LiteralParsingException.hpp"
#include "SymbolTable.hpp"

std::regex parsers::ExpressionParser::char_literal_regex_{ "^[+-]?'.'$" };
std::regex parsers::ExpressionParser::decimal_literal_regex_{ "^[+-]?[1-9][0-9]*$" };
std::regex parsers::ExpressionParser::octal_literal_regex_{ "^[+-]?0[0-7]*$" }; // * instead of + is a hack for parsing 0
std::regex parsers::ExpressionParser::hex_literal_regex_{ "^[+-]?0x[0-9a-f]+$" };

std::regex parsers::ExpressionParser::literal_regex_{ "([+-]?('.'|[1-9][0-9]*|0x[0-9a-f]+|0[0-7]*))" };
std::regex parsers::ExpressionParser::expression_regex_{
    R"((\s*[+-]?\s*('.'|[1-9][0-9]*|0x[0-9a-f]+|0[0-7]*))(\s*[+-]\s*('.'|[1-9][0-9]*|0x[0-9a-f]+|0[0-7]*))*)"
};

std::cmatch parsers::ExpressionParser::match_{};

bool parsers::ExpressionParser::is_literal(const std::string &string)
{
    return is_char_literal(string) || is_decimal_literal(string) ||
           is_octal_literal(string) || is_hex_literal(string);
}

int parsers::ExpressionParser::parse(const std::string &string)
{
    if (is_char_literal(string))
        return parse_char_literal(string);
    if (is_decimal_literal(string))
        return parse_decimal_literal(string);
    if (is_octal_literal(string))
        return parse_octal_literal(string);
    if (is_hex_literal(string))
        return parse_hex_literal(string);

    throw LiteralParsingException();
}

bool parsers::ExpressionParser::is_expression(const std::string &string)
{
    return std::regex_match(string.c_str(), match_, expression_regex_);
}

assembler::word_t parsers::ExpressionParser::evaluate_expression(std::string string)
{
    string.erase(std::remove_if(string.begin(),
                                string.end(),
                                [](int ch) { return std::isspace(ch); }),
                 string.end());

    std::smatch match;
    assembler::word_t expression_value = 0;
    while (std::regex_search(string, match, literal_regex_))
    {
        expression_value += parse(match.str());
        string = match.suffix();
    }

    return expression_value;
}

assembler::word_t parsers::ExpressionParser::evaluate_expression(
    std::string string, std::shared_ptr<assembler::SymbolTable> symbol_table)
{
    string.erase(std::remove_if(string.begin(),
                                string.end(),
                                [](int ch) { return std::isspace(ch); }),
                 string.end());

    if (string[0] != '+' && string[0] != '-')
    {
        string = '+' + string;
    }

    const std::regex regex("[\\+-][^\\+-]+");
    std::smatch match;
    assembler::word_t expression_value = 0;
    while (std::regex_search(string, match, regex))
    {
        std::string operand = match.str();
        if (is_literal(operand))
        {
            expression_value += parse(operand);
        }
        else
        {
            symbol_table->make_declaration(operand.substr(1));
            const int value = symbol_table->at(operand.substr(1)).value;
            expression_value += (operand[0] == '-' ? -value : value);
        }

        string = match.suffix();
    }

    return expression_value;
}

bool parsers::ExpressionParser::is_char_literal(const std::string &string)
{
    return std::regex_match(string.c_str(), match_, char_literal_regex_);
}

bool parsers::ExpressionParser::is_decimal_literal(const std::string &string)
{
    return std::regex_match(string.c_str(), match_, decimal_literal_regex_);
}

bool parsers::ExpressionParser::is_octal_literal(const std::string &string)
{
    return std::regex_match(string.c_str(), match_, octal_literal_regex_);
}

bool parsers::ExpressionParser::is_hex_literal(const std::string &string)
{
    return std::regex_match(string.c_str(), match_, hex_literal_regex_);
}

int parsers::ExpressionParser::parse_char_literal(const std::string &string)
{
    if (string[0] == '-')
        return -string[2];
    if (string[0] == '+')
        return string[2];
    return string[1];
}

int parsers::ExpressionParser::parse_decimal_literal(const std::string &string)
{
    std::stringstream string_stream;
    string_stream << string;
    int decimal_literal;
    string_stream >> std::dec >> decimal_literal;
    return decimal_literal;
}

int parsers::ExpressionParser::parse_octal_literal(const std::string &string)
{
    std::stringstream string_stream;
    string_stream << string;
    int octal_literal;
    string_stream >> std::oct >> std::showbase >> octal_literal;
    return octal_literal;
}

int parsers::ExpressionParser::parse_hex_literal(const std::string &string)
{
    std::stringstream string_stream;
    string_stream << string;
    int hex_literal;
    string_stream >> std::hex >> std::showbase >> hex_literal;
    return hex_literal;
}
