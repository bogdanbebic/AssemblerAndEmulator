#ifndef DATA_DEFINITION_PARSER_H_GUARD
#define DATA_DEFINITION_PARSER_H_GUARD

#include "StatementParser.h"

namespace parsers
{
	class DataDefinitionParser :
		public StatementParser
	{
	public:
		explicit DataDefinitionParser() = default;
		std::shared_ptr<statements::Statement> parse(std::string statement) override;
	private:
		bool can_parse(const std::string& statement) const;

		// TODO: member fields
	};
}

#endif
