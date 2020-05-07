#ifndef LABEL_PARSER_H_GUARD
#define LABEL_PARSER_H_GUARD

#include <string>
#include <regex>
#include <memory>

class SymbolTable;

namespace parsers
{
	class LabelParser
	{
	public:
		explicit LabelParser(std::shared_ptr<SymbolTable> symbol_table);
		std::string parse(std::string line, size_t line_counter);
	private:
		std::regex regex_{ "^(\\w+):\\s*(.*)$" };
		std::cmatch match_;
		
		std::shared_ptr<SymbolTable> symbol_table_;
	};

}

#endif
