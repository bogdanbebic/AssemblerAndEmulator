#include "Parser.h"

#include <string>
#include <sstream>

#include "ParsingException.h"

void parsers::Parser::parse(std::istream &is)
{
	std::string line;
	is >> std::ws;
	while (!this->directive_end_ && std::getline(is, line))
	{
		try
		{
			this->parse_line(line);
		}
		catch (ParsingException &exception)
		{
			// TODO: LOG error
			std::cout << exception.what() << "\n";
		}

		is >> std::ws;
	}
}

void parsers::Parser::parse_line(std::string line)
{
	line = this->label_parser_.parse(line);
	// TODO: parse line
	std::cout << "LINE:'" << line << "'\n";
}
