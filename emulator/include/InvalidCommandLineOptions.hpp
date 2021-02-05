#ifndef _INVALID_COMMAND_LIND_OPTIONS_HPP_
#define _INVALID_COMMAND_LIND_OPTIONS_HPP_

#include <exception>
#include <string>

namespace emulator
{
    namespace utility
    {
        namespace exceptions
        {
            class InvalidCommandLineOptions final : public std::exception
            {
            public:
                explicit InvalidCommandLineOptions(std::string msg)
                    : msg_("invalid cmd options: " + msg)
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
    }     // namespace utility
} // namespace emulator

#endif
