#ifndef _LINKER_ERROR_HPP_
#define _LINKER_ERROR_HPP_

#include <exception>
#include <string>

namespace linker
{
    namespace exceptions
    {
        class LinkerError : public std::exception
        {
        public:
            explicit LinkerError(std::string msg) : msg_("Linker error: " + msg)
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
} // namespace linker

#endif
