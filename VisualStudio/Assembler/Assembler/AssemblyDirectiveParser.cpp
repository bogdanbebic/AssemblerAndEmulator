#include "AssemblyDirectiveParser.h"

#include <utility>
#include <iostream>

parsers::AssemblyDirectiveParser::AssemblyDirectiveParser(std::shared_ptr<assembler::SectionTable> section_table)
	: section_table_(std::move(section_table))
{
	// empty body
}

std::shared_ptr<statements::Statement> parsers::AssemblyDirectiveParser::parse(std::string statement)
{
	if (this->can_parse(statement))
	{
		// TODO: implement
		std::cout << "STATEMENT: '" << statement << "'\n";
		return nullptr;
	}
	
	return StatementParser::parse(statement);
}

bool parsers::AssemblyDirectiveParser::can_parse(std::string statement)
{
	// TODO: implement
	return true;
}
