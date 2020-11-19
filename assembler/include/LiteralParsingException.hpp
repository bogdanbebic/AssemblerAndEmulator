#ifndef _LITERAL_PARSING_EXCEPTION_HPP_
#define _LITERAL_PARSING_EXCEPTION_HPP_

#include "ParsingException.hpp"

namespace parsers
{
    class LiteralParsingException : public ParsingException
    {
    public:
        char const *what() const noexcept override
        {
            return "Invalid literal: allowed literals are chars, decimal, octal, hex integers";
        }
    };
} // namespace parsers

#endif
