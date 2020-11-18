#include "StatementParser.h"

#include <utility>

std::shared_ptr<statements::Statement> parsers::StatementParser::parse(std::string statement)
{
    if (this->next_ != nullptr)
    {
        return this->next_->parse(std::move(statement));
    }

    return nullptr;
}

void parsers::StatementParser::set_next(std::shared_ptr<StatementParser> statement_parser)
{
    this->next_ = std::move(statement_parser);
}
