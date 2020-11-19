#ifndef _STACK_UNDERFLOW_HPP_
#define _STACK_UNDERFLOW_HPP_

#include <exception>

namespace emulator
{
    namespace system
    {
        namespace exceptions
        {
            class StackUnderflow final : public std::exception
            {
            public:
                char const *what() const noexcept override
                {
                    return "Error: stack underflow";
                }
            };
        } // namespace exceptions
    }     // namespace system
} // namespace emulator

#endif
