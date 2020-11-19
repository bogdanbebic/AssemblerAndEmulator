#ifndef _STACK_OVERFLOW_HPP_
#define _STACK_OVERFLOW_HPP_

#include <exception>

namespace emulator
{
    namespace system
    {
        namespace exceptions
        {
            class StackOverflow final : public std::exception
            {
            public:
                char const *what() const noexcept override
                {
                    return "Error: stack overflow";
                }
            };
        } // namespace exceptions
    }     // namespace system
} // namespace emulator

#endif
