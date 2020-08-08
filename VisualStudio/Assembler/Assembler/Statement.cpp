#include "Statement.h"

#include <utility>

statements::Statement::Statement(size_t location_counter_increment, bool is_end, 
                                 bool is_section_end, std::string next_section)
	: location_counter_increment_(location_counter_increment)
	, is_end_(is_end)
	, is_section_end_(is_section_end)
	, next_section_(std::move(next_section))
{
	// empty body
}

bool statements::Statement::is_section_end() const
{
	return this->is_section_end_;
}

size_t statements::Statement::location_counter_increment() const
{
	return this->location_counter_increment_;
}

bool statements::Statement::is_end() const
{
	return this->is_end_;
}

std::string statements::Statement::next_section() const
{
	return this->next_section_;
}
