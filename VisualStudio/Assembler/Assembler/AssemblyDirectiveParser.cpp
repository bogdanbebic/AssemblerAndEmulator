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
		
		const std::regex regex{R"(^\.(global|extern|section|equ)\s*(.*)$)"};
		const std::regex symbol_list_regex{
			R"(^([a-zA-Z_][a-zA-Z_0-9]*)\s*(,\s*([a-zA-Z_][a-zA-Z_0-9]*))*\s*$)"
		};
		const std::regex section_name_regex{ "^([a-zA-Z_][a-zA-Z_0-9]*)\\s*$" };

		std::smatch match;
		if (std::regex_match(statement, match, regex))
		{
			// extract directive
			std::string directive = match[1];
			std::string args = match[2];

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
				// TODO: implement
				
			}

			if (directive == "extern")
			{
				// TODO: implement
				
			}

			if (directive == "equ")
			{
				// TODO: implement
				
			}
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
