#ifndef _MEMORY_ACCESS_VIOLATION_H_
#define _MEMORY_ACCESS_VIOLATION_H_

#include <exception>

namespace emulator
{
	namespace system
	{
		namespace exceptions
		{
			class MemoryAccessViolation final : public std::exception
			{
			public:
				char const* what() const override
				{
					return "Error: Memory access violation";
				}
			};
		}
	}
}

#endif
