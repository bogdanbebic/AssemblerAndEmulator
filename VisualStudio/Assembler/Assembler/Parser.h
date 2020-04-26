#ifndef PARSER_H_GUARD
#define PARSER_H_GUARD

#include <iostream>
#include "LabelParser.h"

namespace parsers
{

	class Parser
	{
	public:
		void parse(std::istream &is);
	private:
		void parse_line(std::string line);
		
		bool directive_end_ = false;
		LabelParser label_parser_;
	};


}


#endif
