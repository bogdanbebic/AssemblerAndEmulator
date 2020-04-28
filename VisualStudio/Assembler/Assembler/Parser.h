#ifndef PARSER_H_GUARD
#define PARSER_H_GUARD

#include <iostream>
#include <memory>
#include "LabelParser.h"
#include "StatementParser.h"

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
		std::shared_ptr<StatementParser> statement_parser_chain_;
	};


}


#endif
