#include "Parser.h"

#include <string>
#include <sstream>

#include "ParsingException.h"

void parsers::Parser::parse(std::istream &is)
{
	std::string line;
	is >> std::ws;
	while (std::getline(is, line))
	{
		try
		{
			bool is_end = this->parse_line(line);
			if (is_end)
			{
				break;
			}
		}
		catch (ParsingException &exception)
		{
			// TODO: LOG error
			std::cerr << exception.what() << "\n";
		}

		is >> std::ws;
	}
}

std::stringstream parsers::Parser::to_school_elf() const
{
	return this->symbol_table_->to_school_elf();
}

bool parsers::Parser::parse_line(const std::string& line)
{
	std::string line_without_comments = this->line_comment_stripper_.strip_line_comment(line);
	std::string statement_line = this->label_parser_.parse(line_without_comments, 0, this->line_counter_);
	if (this->statement_parser_chain_ == nullptr)
	{
		return false;
	}
	
	const std::shared_ptr<statements::Statement> statement = this->statement_parser_chain_->parse(statement_line);
	std::cout << "LINE:'" << line << "'\n";
	if (statement != nullptr)
	{
		return statement->is_end();
	}

	return false;
}
