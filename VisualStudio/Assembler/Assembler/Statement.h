#ifndef STATEMENT_H_GUARD
#define STATEMENT_H_GUARD

#include <cstddef>

namespace statements
{
	class Statement
	{
	public:
		Statement(size_t location_counter_increment, bool is_end);

		size_t location_counter_increment() const;
		bool is_end() const;
	private:
		size_t location_counter_increment_ = 0;
		bool is_end_ = false;
	};
}


#endif
