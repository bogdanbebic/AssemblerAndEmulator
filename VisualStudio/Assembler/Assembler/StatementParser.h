#ifndef STATEMENT_PARSER_H_GUARD
#define STATEMENT_PARSER_H_GUARD

#include <string>
#include <memory>

namespace parsers
{
	class StatementParser  // NOLINT(cppcoreguidelines-special-member-functions, hicpp-special-member-functions)
	{
	public:
		virtual ~StatementParser() = default;

		virtual size_t parse(std::string statement) = 0;

		void set_next(std::shared_ptr<StatementParser> statement_parser);
	protected:
		std::shared_ptr<StatementParser> next_{ nullptr };
	};	
}

#endif
