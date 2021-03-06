#ifndef _MEMORY_ACCESS_VIOLATION_HPP_
#define _MEMORY_ACCESS_VIOLATION_HPP_

#include <exception>
#include <string>

namespace emulator
{
    namespace system
    {
        namespace exceptions
        {
            class MemoryAccessViolation final : public std::exception
            {
            public:
                explicit MemoryAccessViolation(std::string msg)
                    : msg_("Memory access violation: " + msg)
                {
                }

                char const *what() const noexcept override
                {
                    return this->msg_.c_str();
                }

            private:
                std::string msg_;
            };
        } // namespace exceptions
    }     // namespace system
} // namespace emulator

#endif
