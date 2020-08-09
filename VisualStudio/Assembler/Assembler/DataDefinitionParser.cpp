#include "DataDefinitionParser.h"

#include <regex>
#include <stdexcept>

#include "LiteralParser.h"

#include <iostream>

std::shared_ptr<statements::Statement> parsers::DataDefinitionParser::parse(std::string statement)
{
	if (this->can_parse(statement))
	{
		std::cout << "DATA_DEF: '" << statement << "'\n";
		const std::regex data_skip_regex{R"(^\.skip\s+([^\s]+)\s*$)"};
		// const std::regex data_def_regex{ "^\\.(byte|word)\\s+()" };
		std::smatch match;
		
		if (std::regex_match(statement, match, data_skip_regex))
		{
			const auto arg = match[1].str();
			std::cout << "literal:'" + arg + "'\n";
			if (LiteralParser::is_literal(arg))
			{
				int literal = LiteralParser::parse(arg);
				return std::make_shared<statements::Statement>(literal, false);
			}
			else
			{
				throw std::invalid_argument{ "Invalid argument for skip directive" };
			}
		}
	}
	
	return StatementParser::parse(statement);
}

bool parsers::DataDefinitionParser::can_parse(const std::string& statement) const
{
	const std::regex data_definitions_regex{ "^\\.(skip|byte|word)\\s+.*$" };
	return std::regex_match(statement, data_definitions_regex);
}
