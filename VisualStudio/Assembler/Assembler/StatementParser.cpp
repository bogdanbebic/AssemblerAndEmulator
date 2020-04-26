#include "StatementParser.h"

#include <utility>

void parsers::StatementParser::set_next(std::shared_ptr<StatementParser> statement_parser)
{
	this->next_ = std::move(statement_parser);
}
