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
		const std::regex zero_operand_regex{
	"^(halt"
		"|iret"
		"|ret)"
		"\\s*$"
		};

		const std::regex one_operand_regex{
	"^((int"
		"|call"
		"|jmp"
		"|jeq"
		"|jne"
		"|jgt"
		"|push"
		"|pop)"
		"[bw]?)"
		"\\s+([^,\\s]+)\\s*$"
		};

		const std::regex two_operand_regex{
	"^((xchg"
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
		"[bw]?)"
		"\\s+([^,\\s]+)\\s*,\\s*([^,\\s]+)\\s*$"
		};
		
		std::smatch match;
		if (std::regex_match(statement, match, zero_operand_regex))
		{
			std::cout << "INSTRUCTION 0:'" << statement << "'" << match[1].str() << "\n";
			
			return nullptr;
		}

		if (std::regex_match(statement, match, one_operand_regex))
		{
			std::string mnemonic = match[1].str();
			std::string short_mnemonic = match[2].str();
			constexpr char DEFAULT_SIZE_OPERAND_SPECIFIER = 'w';
			if (short_mnemonic == mnemonic)
			{
				mnemonic = mnemonic + DEFAULT_SIZE_OPERAND_SPECIFIER;
			}

			char operand_size_specifier = mnemonic.back();
			std::cout << "INSTRUCTION 1:'" << statement << "'" << mnemonic << "\n";

			return nullptr;
		}

		if (std::regex_match(statement, match, two_operand_regex))
		{
			std::string mnemonic = match[1].str();
			std::string short_mnemonic = match[2].str();
			constexpr char DEFAULT_SIZE_OPERAND_SPECIFIER = 'w';
			if (short_mnemonic == mnemonic)
			{
				mnemonic = mnemonic + DEFAULT_SIZE_OPERAND_SPECIFIER;
			}
			
			std::cout << "INSTRUCTION 2:'" << statement << "'" << mnemonic << "\n";

			return nullptr;
		}

		throw std::invalid_argument{ "Invalid number of operands for instruction: " + statement };
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
