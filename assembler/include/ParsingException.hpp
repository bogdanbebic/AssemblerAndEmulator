#ifndef _PARSING_EXCEPTION_HPP_
#define _PARSING_EXCEPTION_HPP_

#include <exception>

namespace parsers
{

    class ParsingException : public std::exception
    {
    public:
        char const *what() const noexcept override
        {
            return "Invalid label: label must be an identifier followed by a colon.";
        }
    };

} // namespace parsers

#endif
