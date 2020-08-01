#include "LabelParser.h"
#include <iostream>
#include <utility>

#include "ParsingException.h"
#include "SymbolTable.h"

parsers::LabelParser::LabelParser(std::shared_ptr<assembler::SymbolTable> symbol_table)
	: symbol_table_(std::move(symbol_table))
{
	// empty body
}

std::string parsers::LabelParser::parse(std::string line, size_t section_index, size_t line_counter)
{
	if (line.find(':') != std::string::npos)
	{
		if (std::regex_match(line.c_str(), this->match_, this->regex_))
		{
			std::cout << "LABEL:'" << this->match_[1].str() << "'\n";
			std::string symbol = this->match_[1].str();
			assembler::SymbolTable::SymbolTableEntry entry = { symbol, line_counter, section_index, false };

			// TODO: check if already exists - maybe throw an exception
			this->symbol_table_->insert({ symbol, entry });
			
			return this->match_[2].str();
		}

		throw ParsingException{};
	}

	return line;
}
