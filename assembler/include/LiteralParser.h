#ifndef LITERAL_PARSER_H_GUARD
#define LITERAL_PARSER_H_GUARD
#include <memory>
#include <regex>
#include <string>

#include "SymbolTable.h"

namespace parsers
{
    class LiteralParser
    {
    public:
        static bool is_literal(const std::string &string);
        static int parse(const std::string &string);
        static bool is_expression(const std::string &string);
        static int evaluate_expression(std::string string);
        static int evaluate_expression(std::string string,
                                       std::shared_ptr<assembler::SymbolTable> symbol_table);

    private:
        static std::regex char_literal_regex_;
        static std::regex decimal_literal_regex_;
        static std::regex octal_literal_regex_;
        static std::regex hex_literal_regex_;

        static std::regex literal_regex_;
        static std::regex expression_regex_;

        static std::cmatch match_;

        static bool is_char_literal(const std::string &string);
        static bool is_decimal_literal(const std::string &string);
        static bool is_octal_literal(const std::string &string);
        static bool is_hex_literal(const std::string &string);

        static int parse_char_literal(const std::string &string);
        static int parse_decimal_literal(const std::string &string);
        static int parse_octal_literal(const std::string &string);
        static int parse_hex_literal(const std::string &string);
    };
} // namespace parsers

#endif
