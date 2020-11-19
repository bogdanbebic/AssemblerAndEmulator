#pragma once
#include "ParsingException.h"

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
