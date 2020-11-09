#include "DataDefinitionParser.h"

#include <regex>
#include <stdexcept>
#include <sstream>

#include "LiteralParser.h"

#include <iostream>

parsers::DataDefinitionParser::DataDefinitionParser(std::shared_ptr<assembler::ObjectCodeArray> object_code)
	: object_code_(object_code)
{
	// empty body
}

std::shared_ptr<statements::Statement> parsers::DataDefinitionParser::parse(std::string statement)
{
	if (this->can_parse(statement))
	{
		std::cout << "DATA_DEF: '" << statement << "'\n";
		const std::regex data_skip_regex{R"(^\.skip\s+([^\s]+)\s*$)"};
		const std::regex data_byte_regex{R"(^\.byte\s+(.+)$)"};
		const std::regex data_word_regex{R"(^\.word\s+(.+)$)"};
		std::smatch match;
		
		if (std::regex_match(statement, match, data_skip_regex))
		{
			const auto arg = match[1].str();
			std::cout << "literal:'" + arg + "'\n";
			if (LiteralParser::is_literal(arg))
			{
				int literal = LiteralParser::parse(arg);
				this->object_code_->skip_bytes(literal);
				return std::make_shared<statements::Statement>(literal, false);
			}
			else
			{
				throw std::invalid_argument{ "Invalid argument for skip directive" };
			}
		}

		if (std::regex_match(statement, match, data_byte_regex))
		{
			std::stringstream ss(match[1].str());
			std::string byte_def;

			while (std::getline(ss, byte_def, ','))
			{
				std::cout << byte_def << std::endl;
				// TODO: implement
			}
		}

		if (std::regex_match(statement, match, data_word_regex))
		{
			std::stringstream ss(match[1].str());
			std::string word_def;

			while (std::getline(ss, word_def, ','))
			{
				std::cout << word_def << std::endl;
				// TODO: implement
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
