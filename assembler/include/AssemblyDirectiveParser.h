#ifndef ASSEMBLY_DIRECTIVE_PARSER_H_GUARD
#define ASSEMBLY_DIRECTIVE_PARSER_H_GUARD

#include "StatementParser.h"
#include "SectionTable.h"
#include "SymbolTable.h"

namespace parsers
{
	class AssemblyDirectiveParser :
		public StatementParser
	{
	public:
		explicit AssemblyDirectiveParser(std::shared_ptr<assembler::SectionTable> section_table,
										 std::shared_ptr<assembler::SymbolTable> symbol_table);
		std::shared_ptr<statements::Statement> parse(std::string statement) override;
	private:
		bool can_parse(const std::string& statement) const;
		std::shared_ptr<assembler::SectionTable> section_table_;
		std::shared_ptr<assembler::SymbolTable> symbol_table_;
	};
}

#endif
