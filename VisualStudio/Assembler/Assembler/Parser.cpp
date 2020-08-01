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
			std::cout << exception.what() << "\n";
		}

		is >> std::ws;
	}
}

bool parsers::Parser::parse_line(const std::string& line)
{
	std::string statement_line = this->label_parser_.parse(line, this->line_counter_);

	// TODO: remove
	this->line_counter_ += 4;
	
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
