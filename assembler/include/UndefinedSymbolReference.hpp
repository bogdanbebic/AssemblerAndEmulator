#ifndef _UNDEFINED_SYMBOL_REFERENCE_HPP_
#define _UNDEFINED_SYMBOL_REFERENCE_HPP_

#include <stdexcept>

namespace assembler
{
    class UndefinedSymbolReference : public std::exception
    {
    public:
        char const *what() const noexcept override
        {
            return "Undefined reference: local symbol used but never defined";
        }
    };
} // namespace assembler

#endif
