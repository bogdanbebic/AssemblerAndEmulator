#include "DataDefinitionParser.h"

#include <regex>
#include <stdexcept>
#include <sstream>

#include "LiteralParser.h"

#include <iostream>

parsers::DataDefinitionParser::DataDefinitionParser(std::shared_ptr<assembler::ObjectCodeArray> object_code,
													std::shared_ptr<assembler::SymbolTable> symbol_table)
	: object_code_(object_code)
	, symbol_table_(symbol_table)
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
			size_t bytes_defs_count = 0;
			while (std::getline(ss, byte_def, ','))
			{
				std::cout << byte_def;
				auto value = LiteralParser::evaluate_expression(byte_def, this->symbol_table_);
				std::cout << " : " << value << std::endl;
				this->object_code_->push_back_byte(static_cast<assembler::byte_t>(value));
				bytes_defs_count++;
			}

			return std::make_shared<statements::Statement>(bytes_defs_count * sizeof(assembler::byte_t), false);
		}

		if (std::regex_match(statement, match, data_word_regex))
		{
			std::stringstream ss(match[1].str());
			std::string word_def;
			size_t word_defs_count = 0;
			while (std::getline(ss, word_def, ','))
			{
				std::cout << word_def;
				auto value = LiteralParser::evaluate_expression(word_def, this->symbol_table_);
				std::cout << " : " << value << std::endl;
				this->object_code_->push_back_word(static_cast<assembler::word_t>(value));
				word_defs_count++;
			}
			return std::make_shared<statements::Statement>(word_defs_count * sizeof(assembler::word_t), false);
		}
	}
	
	return StatementParser::parse(statement);
}

bool parsers::DataDefinitionParser::can_parse(const std::string& statement) const
{
	const std::regex data_definitions_regex{ "^\\.(skip|byte|word)\\s+.*$" };
	return std::regex_match(statement, data_definitions_regex);
}
