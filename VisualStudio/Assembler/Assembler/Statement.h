#ifndef STATEMENT_H_GUARD
#define STATEMENT_H_GUARD

#include <cstddef>

namespace statements
{
	class Statement  // NOLINT(hicpp-special-member-functions, cppcoreguidelines-special-member-functions)
	{
	public:
		virtual ~Statement() = default;
		virtual size_t location_counter_increment() const = 0;
		virtual bool is_end() const;
	};
}


#endif
