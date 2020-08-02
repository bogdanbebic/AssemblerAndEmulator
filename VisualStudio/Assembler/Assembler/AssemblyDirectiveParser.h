#ifndef ASSEMBLY_DIRECTIVE_PARSER_H_GUARD
#define ASSEMBLY_DIRECTIVE_PARSER_H_GUARD

#include "StatementParser.h"
#include "SectionTable.h"

namespace parsers
{
	class AssemblyDirectiveParser :
		public StatementParser
	{
	public:
		explicit AssemblyDirectiveParser(std::shared_ptr<assembler::SectionTable> section_table);
		std::shared_ptr<statements::Statement> parse(std::string statement) override;
	private:
		bool can_parse(std::string statement);
		std::shared_ptr<assembler::SectionTable> section_table_;
	};
}

#endif
