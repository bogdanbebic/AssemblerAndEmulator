#ifndef _REGISTER_DIRECT_PARSER_HPP_
#define _REGISTER_DIRECT_PARSER_HPP_

#include "OperandParser.hpp"

namespace parsers
{
    class RegisterDirectParser final : public OperandParser
    {
    public:
        statement::operand_t parse(std::string operand) override;

    private:
        bool can_parse(std::string operand);
    };
} // namespace parsers

#endif
