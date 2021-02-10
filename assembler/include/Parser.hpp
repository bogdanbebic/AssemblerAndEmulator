#ifndef _PARSER_HPP_
#define _PARSER_HPP_

#include <iostream>
#include <memory>
#include <sstream>

#include "LabelParser.hpp"
#include "LineCommentStripper.hpp"
#include "ObjectCodeArray.hpp"
#include "RelocationTable.hpp"
#include "SectionTable.hpp"
#include "StatementParser.hpp"
#include "SymbolTable.hpp"

namespace parsers
{
    class Parser
    {
    public:
        Parser();
        void parse(std::istream &is);
        std::stringstream to_school_elf() const;

    private:
        bool parse_line(const std::string &line);

        size_t line_counter_          = 0;
        size_t current_section_index_ = 1;
        assembler::SectionTable::key_type current_section_name_{
            assembler::SectionTable::undefined_section_entry_name
        };

        std::shared_ptr<assembler::SymbolTable> symbol_table_ =
            std::make_shared<assembler::SymbolTable>();
        std::shared_ptr<assembler::SectionTable> section_table_ =
            std::make_shared<assembler::SectionTable>();
        std::shared_ptr<assembler::ObjectCodeArray> object_code_ =
            std::make_shared<assembler::ObjectCodeArray>();
        std::shared_ptr<assembler::RelocationTable> relocation_table_ =
            std::make_shared<assembler::RelocationTable>(this->symbol_table_,
                                                         this->object_code_);

        LineCommentStripper line_comment_stripper_;
        LabelParser label_parser_{ symbol_table_ };
        std::shared_ptr<StatementParser> statement_parser_chain_ = nullptr;
    };

} // namespace parsers

#endif
