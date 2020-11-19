#ifndef _MEMORY_ACCESS_VIOLATION_HPP_
#define _MEMORY_ACCESS_VIOLATION_HPP_

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
                char const *what() const noexcept override
                {
                    return "Error: Memory access violation";
                }
            };
        } // namespace exceptions
    }     // namespace system
} // namespace emulator

#endif
