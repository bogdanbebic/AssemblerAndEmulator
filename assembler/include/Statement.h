#ifndef STATEMENT_H_GUARD
#define STATEMENT_H_GUARD

#include <cstddef>
#include <string>

namespace statements
{
	class Statement
	{
	public:
		Statement(size_t location_counter_increment, bool is_end, bool is_section_end = false, std::string next_section = "");

		bool is_section_end() const;
		size_t location_counter_increment() const;
		bool is_end() const;
		std::string next_section() const;
	private:
		size_t location_counter_increment_ = 0;
		bool is_end_ = false;
		bool is_section_end_ = false;
		std::string next_section_;
	};
}


#endif
