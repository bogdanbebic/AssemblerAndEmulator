#include "InstructionParser.h"

#include <utility>

parsers::InstructionParser::InstructionParser(std::shared_ptr<assembler::SymbolTable> symbol_table,
                                              std::shared_ptr<assembler::ObjectCodeArray> object_code)
	: symbol_table_(std::move(symbol_table))
	, object_code_(std::move(object_code))
{
	// empty body
}

std::shared_ptr<statements::Statement> parsers::InstructionParser::parse(std::string statement)
{
	if (this->can_parse(statement))
	{
		// TODO: implement
	}
	
	return StatementParser::parse(statement);
}

bool parsers::InstructionParser::can_parse(const std::string& statement) const
{
	// TODO: implement
	return false;
}
