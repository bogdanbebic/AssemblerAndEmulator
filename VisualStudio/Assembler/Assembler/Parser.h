#ifndef PARSER_H_GUARD
#define PARSER_H_GUARD

#include <iostream>
#include <memory>
#include "LabelParser.h"
#include "StatementParser.h"

#include "SymbolTable.h"
#include "SectionTable.h"

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

		assembler::SymbolTable symbol_table_;
		assembler::SectionTable section_table_;
				
		LabelParser label_parser_{std::shared_ptr<assembler::SymbolTable>(&symbol_table_)};
		std::shared_ptr<StatementParser> statement_parser_chain_ = nullptr;

	};


}


#endif
