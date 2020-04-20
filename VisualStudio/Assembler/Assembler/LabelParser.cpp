#include "LabelParser.h"
#include <iostream>

#include "ParsingException.h"

std::string parsers::LabelParser::parse(std::string line)
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
