#include "LabelParser.h"
#include <iostream>
#include <utility>

#include "ParsingException.h"

parsers::LabelParser::LabelParser(std::shared_ptr<SymbolTable> symbol_table)
	: symbol_table_(std::move(symbol_table))
{
	// empty body
}

std::string parsers::LabelParser::parse(std::string line, size_t line_counter)
{
	if (line.find(':') != std::string::npos)
	{
		if (std::regex_match(line.c_str(), this->match_, this->regex_))
		{
			std::cout << "LABEL:'" << this->match_[1].str() << "'\n";
			// TODO: add label to symbol table
			return this->match_[2].str();
		}
		else
		{
			throw ParsingException{};
		}
	}

	return line;
}
