#ifndef _LABEL_PARSER_HPP_
#define _LABEL_PARSER_HPP_

#include <memory>
#include <regex>
#include <string>

namespace assembler
{
    class SymbolTable;
}

namespace parsers
{
    class LabelParser
    {
    public:
        explicit LabelParser(std::shared_ptr<assembler::SymbolTable> symbol_table);
        std::string parse(std::string line, size_t section_index, size_t line_counter);

    private:
        std::regex regex_{ "^(\\w+):\\s*(.*)$" };
        std::cmatch match_;

        std::shared_ptr<assembler::SymbolTable> symbol_table_;
    };

} // namespace parsers

#endif
