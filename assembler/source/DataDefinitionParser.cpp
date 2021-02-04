#include "DataDefinitionParser.hpp"

#include <regex>
#include <sstream>
#include <stdexcept>

#include "ExpressionParser.hpp"
#include "ObjectCodeArray.hpp"
#include "RelocationTable.hpp"
#include "SymbolTable.hpp"

#include <iostream>

parsers::DataDefinitionParser::DataDefinitionParser(
    std::shared_ptr<assembler::ObjectCodeArray> object_code,
    std::shared_ptr<assembler::SymbolTable> symbol_table,
    std::shared_ptr<assembler::RelocationTable> relocation_table)
    : object_code_(object_code), symbol_table_(symbol_table), relocation_table_(relocation_table)
{
    // empty body
}

std::shared_ptr<statements::Statement> parsers::DataDefinitionParser::parse(std::string statement)
{
    if (this->can_parse(statement))
    {
        const std::regex data_skip_regex{ R"(^\.skip\s+([^\s]+)\s*$)" };
        const std::regex data_byte_regex{ R"(^\.byte\s+(.+)$)" };
        const std::regex data_word_regex{ R"(^\.word\s+(.+)$)" };

        const std::regex single_symbol{ "\\s*(\\w+|'.'|[1-9][0-9]*|0x[0-9a-f]+|0[0-7]*)\\s*" };

        std::smatch match;

        if (std::regex_match(statement, match, data_skip_regex))
        {
            const auto arg = match[1].str();
            if (ExpressionParser::is_literal(arg))
            {
                int literal = ExpressionParser::parse(arg);
                this->object_code_->skip_bytes(literal);
                return std::make_shared<statements::Statement>(literal, false);
            }
            else
            {
                throw std::invalid_argument{ "Invalid argument for skip directive" };
            }
        }

        if (std::regex_match(statement, match, data_byte_regex))
        {
            std::stringstream ss(match[1].str());
            std::string byte_def;
            size_t bytes_defs_count = 0;
            while (std::getline(ss, byte_def, ','))
            {
                if (!std::regex_match(byte_def, single_symbol))
                    throw std::invalid_argument{ "Invalid argument for .byte directive" };

                auto value = ExpressionParser::evaluate_expression(byte_def, this->symbol_table_);

                byte_def.erase(
                    std::remove_if(byte_def.begin(),
                                   byte_def.end(),
                                   [](int ch) { return std::isspace(ch); }),
                    byte_def.end());
                if (!ExpressionParser::is_literal(byte_def))
                    this->add_byte_relocation(byte_def);

                this->object_code_->push_back_byte(static_cast<assembler::byte_t>(value));
                bytes_defs_count++;
            }

            return std::make_shared<statements::Statement>(
                bytes_defs_count * sizeof(assembler::byte_t), false);
        }

        if (std::regex_match(statement, match, data_word_regex))
        {
            std::stringstream ss(match[1].str());
            std::string word_def;
            size_t word_defs_count = 0;
            while (std::getline(ss, word_def, ','))
            {
                if (!std::regex_match(word_def, single_symbol))
                    throw std::invalid_argument{ "Invalid argument for .word directive" };

                auto value = ExpressionParser::evaluate_expression(word_def, this->symbol_table_);

                word_def.erase(
                    std::remove_if(word_def.begin(),
                                   word_def.end(),
                                   [](int ch) { return std::isspace(ch); }),
                    word_def.end());
                if (!ExpressionParser::is_literal(word_def))
                    this->add_word_relocation(word_def);

                this->object_code_->push_back_word(static_cast<assembler::word_t>(value));
                word_defs_count++;
            }
            return std::make_shared<statements::Statement>(
                word_defs_count * sizeof(assembler::word_t), false);
        }
    }

    return StatementParser::parse(statement);
}

bool parsers::DataDefinitionParser::can_parse(const std::string &statement) const
{
    const std::regex data_definitions_regex{ "^\\.(skip|byte|word)\\s+.*$" };
    return std::regex_match(statement, data_definitions_regex);
}

void parsers::DataDefinitionParser::add_byte_relocation(std::string symbol)
{
    auto relocation_type = this->symbol_table_->is_defined(symbol)
                               ? assembler::RelocationTable::R_SECTION8
                               : assembler::RelocationTable::R_8;
    this->relocation_table_->insert(
        { symbol, relocation_type, this->object_code_->size() });
}

void parsers::DataDefinitionParser::add_word_relocation(std::string symbol)
{
    auto relocation_type = this->symbol_table_->is_defined(symbol)
                               ? assembler::RelocationTable::R_SECTION16
                               : assembler::RelocationTable::R_16;
    this->relocation_table_->insert(
        { symbol, relocation_type, this->object_code_->size() });
}
