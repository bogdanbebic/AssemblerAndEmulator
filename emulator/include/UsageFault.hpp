#ifndef _USAGE_FAULT_HPP_
#define _USAGE_FAULT_HPP_

#include <exception>
#include <string>

namespace emulator
{
    namespace system
    {
        namespace exceptions
        {
            class UsageFault : std::exception
            {
            public:
                explicit UsageFault(std::string msg)
                    : msg_("Usage fault: " + msg)
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
