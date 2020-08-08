#include "AssemblyDirectiveParser.h"

#include <utility>
#include <iostream>
#include <regex>

parsers::AssemblyDirectiveParser::AssemblyDirectiveParser(std::shared_ptr<assembler::SectionTable> section_table)
	: section_table_(std::move(section_table))
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
		
		const std::regex regex{ "^\\.(global|extern|section|equ)\\s*(.*)$" };
		const std::regex symbol_list_regex{
			"^([a-zA-Z_][a-zA-Z_0-9]*)\\s*(,\\s*([a-zA-Z_][a-zA-Z_0-9]*))*$"
		};
		const std::regex section_name_regex{ "^([a-zA-Z_][a-zA-Z_0-9]*)$" };

		std::smatch match;
		if (std::regex_match(statement, match, regex))
		{
			// extract directive
			std::string directive = match[1];
			std::string args = match[2];
			std::cout << "directive: '" << directive << "'\n"
				<< "args: '" << args << "'\n";

			// TODO: implement
		}
		
		return nullptr;
	}
	
	return StatementParser::parse(statement);
}

bool parsers::AssemblyDirectiveParser::can_parse(const std::string& statement) const
{
	const std::regex directive_end_regex{ "^\\.end\\s*$" };
	const std::regex regex{ "^\\.(global|extern|section|equ)\\s+.*$" };
	return std::regex_match(statement, directive_end_regex) || std::regex_match(statement, regex);
}
