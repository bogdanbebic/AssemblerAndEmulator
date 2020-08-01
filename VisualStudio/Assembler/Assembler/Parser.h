#ifndef PARSER_H_GUARD
#define PARSER_H_GUARD

#include <iostream>
#include <memory>
#include "LabelParser.h"
#include "StatementParser.h"

#include "SymbolTable.h"
#include "SectionTable.h"
#include "LineCommentStripper.h"

namespace parsers
{
	class Parser
	{
	public:
		void parse(std::istream &is);
	private:
		bool parse_line(const std::string& line);

		size_t line_counter_ = 0;
		assembler::SectionTable::key_type current_section_name_ = 
		{
			assembler::SectionTable::undefined_section_entry_name
		};

		std::shared_ptr<assembler::SymbolTable> symbol_table_ = std::make_shared<assembler::SymbolTable>();
		std::shared_ptr<assembler::SectionTable> section_table_ = std::make_shared<assembler::SectionTable>();

		LineCommentStripper line_comment_stripper_;
		LabelParser label_parser_{ symbol_table_ };
		std::shared_ptr<StatementParser> statement_parser_chain_ = nullptr;

	};


}


#endif
