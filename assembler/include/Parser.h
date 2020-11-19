#ifndef PARSER_H_GUARD
#define PARSER_H_GUARD

#include <iostream>
#include <memory>
#include <sstream>

#include "LabelParser.h"
#include "LineCommentStripper.h"
#include "ObjectCodeArray.h"
#include "SectionTable.h"
#include "StatementParser.h"
#include "SymbolTable.h"

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
        size_t current_section_index_ = 0;
        assembler::SectionTable::key_type current_section_name_{
            assembler::SectionTable::undefined_section_entry_name
        };

        std::shared_ptr<assembler::SymbolTable> symbol_table_ =
            std::make_shared<assembler::SymbolTable>();
        std::shared_ptr<assembler::SectionTable> section_table_ =
            std::make_shared<assembler::SectionTable>();
        std::shared_ptr<assembler::ObjectCodeArray> object_code_ =
            std::make_shared<assembler::ObjectCodeArray>();

        LineCommentStripper line_comment_stripper_;
        LabelParser label_parser_{ symbol_table_ };
        std::shared_ptr<StatementParser> statement_parser_chain_ = nullptr;
    };

} // namespace parsers

#endif
