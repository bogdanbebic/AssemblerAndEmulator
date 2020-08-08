#include "Statement.h"

statements::Statement::Statement(size_t location_counter_increment, bool is_end)
	: location_counter_increment_(location_counter_increment)
	, is_end_(is_end)
{
	// empty body
}

size_t statements::Statement::location_counter_increment() const
{
	return this->location_counter_increment_;
}

bool statements::Statement::is_end() const
{
	return this->is_end_;
}
