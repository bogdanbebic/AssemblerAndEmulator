#include "AssemblyDirectiveParser.hpp"

#include <iostream>
#include <regex>
#include <utility>

#include "SectionTable.hpp"
#include "SymbolTable.hpp"

parsers::AssemblyDirectiveParser::AssemblyDirectiveParser(
    std::shared_ptr<assembler::SectionTable> section_table,
    std::shared_ptr<assembler::SymbolTable> symbol_table)
    : section_table_(std::move(section_table)), symbol_table_(std::move(symbol_table))
{
    // empty body
}

std::shared_ptr<statements::Statement> parsers::AssemblyDirectiveParser::parse(std::string statement)
{
    if (this->can_parse(statement))
    {
        std::cout << "DIRECTIVE: '" << statement << "'\n";
        const std::regex directive_end_regex{ "^\\.end\\s*$" };
        if (std::regex_match(statement, directive_end_regex))
        {
            return std::make_shared<statements::Statement>(0, true);
        }

        const std::regex regex{ R"(^\.(global|extern|section)\s*(.*)$)" };
        const std::regex symbol_regex{ "([a-zA-Z_][a-zA-Z_0-9]*)" };
        const std::regex symbol_list_regex{ R"(^([a-zA-Z_][a-zA-Z_0-9]*)\s*(,\s*([a-zA-Z_][a-zA-Z_0-9]*))*\s*$)" };
        const std::regex section_name_regex{ "^([a-zA-Z_][a-zA-Z_0-9]*):\\s*$" };

        std::smatch match;
        if (std::regex_match(statement, match, regex))
        {
            // extract directive
            std::string directive = match[1];
            std::string args      = match[2];

            // TODO: delete
            std::cout << "directive: '" << directive << "'\n"
                      << "args: '" << args << "'\n";

            if (directive == "section")
            {
                if (!std::regex_match(args, match, section_name_regex))
                {
                    throw std::invalid_argument{ "Invalid args for .section directive" };
                }

                std::string section_name = match[1];
                this->section_table_->insert(section_name);
                return std::make_shared<statements::Statement>(0, false, true, section_name);
            }

            if (directive == "global")
            {
                if (std::regex_match(args, match, symbol_list_regex))
                {
                    std::cout << "GLOBAL\n";
                    auto symbol_list_begin =
                        std::sregex_iterator(args.begin(), args.end(), symbol_regex);
                    auto symbol_list_end = std::sregex_iterator();
                    for (auto it = symbol_list_begin; it != symbol_list_end; ++it)
                    {
                        auto symbol = it->str();
                        this->symbol_table_->make_global(symbol);
                        std::cout << "'" << it->str() << "'\n";
                    }
                }
                else
                {
                    throw std::invalid_argument{ "Invalid args for .global directive" };
                }
            }

            if (directive == "extern")
            {
                if (std::regex_match(args, match, symbol_list_regex))
                {
                    std::cout << "EXTERN\n";
                    auto symbol_list_begin =
                        std::sregex_iterator(args.begin(), args.end(), symbol_regex);
                    auto symbol_list_end = std::sregex_iterator();
                    for (auto it = symbol_list_begin; it != symbol_list_end; ++it)
                    {
                        auto symbol = it->str();
                        this->symbol_table_->make_extern(symbol);
                        std::cout << "'" << it->str() << "'\n";
                    }
                }
                else
                {
                    throw std::invalid_argument{ "Invalid args for .extern directive" };
                }
            }
        }

        return nullptr;
    }

    return StatementParser::parse(statement);
}

bool parsers::AssemblyDirectiveParser::can_parse(const std::string &statement) const
{
    const std::regex directive_end_regex{ "^\\.end\\s*$" };
    const std::regex regex{ "^\\.(global|extern|section)\\s+.*$" };
    return std::regex_match(statement, directive_end_regex) ||
           std::regex_match(statement, regex);
}
