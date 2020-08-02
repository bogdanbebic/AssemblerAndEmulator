#ifndef STATEMENT_PARSER_H_GUARD
#define STATEMENT_PARSER_H_GUARD

#include <string>
#include <memory>
#include "Statement.h"

namespace parsers
{
	class StatementParser  // NOLINT(cppcoreguidelines-special-member-functions, hicpp-special-member-functions)
	{
	public:
		virtual std::shared_ptr<statements::Statement> parse(std::string statement);
		void set_next(std::shared_ptr<StatementParser> statement_parser);

		StatementParser() = default;
		StatementParser(const StatementParser&) = default;
		StatementParser(StatementParser&&) = default;
		virtual ~StatementParser() = default;
	protected:
		std::shared_ptr<StatementParser> next_{ nullptr };
	};	
}

#endif
