#include "InstructionParser.h"

#include <utility>
#include <regex>
#include <iostream>

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
		std::cout << "INSTRUCTION:'" << statement << "'\n";
	}
	
	return StatementParser::parse(statement);
}

bool parsers::InstructionParser::can_parse(const std::string& statement) const
{
	const std::regex instructions_regex{
	"^(halt"
		"|iret"
		"|ret"
		"|int"
		"|call"
		"|jmp"
		"|jeq"
		"|jne"
		"|jgt"
		"|push"
		"|pop"
		"|xchg"
		"|mov"
		"|add"
		"|sub"
		"|mul"
		"|div"
		"|cmp"
		"|not"
		"|and"
		"|or"
		"|xor"
		"|test"
		"|shl"
		"|shr)"
		".*$"
	};
	
	return std::regex_match(statement, instructions_regex);
}
