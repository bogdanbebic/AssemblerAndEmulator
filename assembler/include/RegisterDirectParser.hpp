#ifndef _REGISTER_DIRECT_PARSER_HPP_
#define _REGISTER_DIRECT_PARSER_HPP_

#include "OperandParser.hpp"

namespace parsers
{
    class RegisterDirectParser final : public OperandParser
    {
    public:
        std::shared_ptr<statement::operand_t> parse(std::string operand) override;

    private:
        bool can_parse(const std::string &operand) const;
    };
} // namespace parsers

#endif