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
		bool parse_line(const std::string& line);

		LabelParser label_parser_{nullptr};
		std::shared_ptr<StatementParser> statement_parser_chain_ = nullptr;
		size_t line_counter_ = 0;
	};


}


#endif
