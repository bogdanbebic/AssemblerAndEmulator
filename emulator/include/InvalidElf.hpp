#ifndef _INVALID_ELF_HPP_
#define _INVALID_ELF_HPP_

#include <exception>
#include <string>

namespace linker
{
    namespace elf
    {
        namespace exceptions
        {
            class InvalidElf : public std::exception
            {
            public:
                explicit InvalidElf(std::string msg)
                    : msg_("Invalid elf: " + msg)
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
    }     // namespace elf
} // namespace linker

#endif
