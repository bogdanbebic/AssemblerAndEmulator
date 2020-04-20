#ifndef LABEL_PARSER_H_GUARD
#define LABEL_PARSER_H_GUARD

#include <string>
#include <regex>

namespace parsers
{
		
	class LabelParser
	{
	public:
		std::string parse(std::string line);
	private:
		std::regex regex_{ "^(\\w+):\\s*(.*)$" };
		std::cmatch match_;
	};

}

#endif
