#ifndef _REGISTER_INDIRECT_PARSER_HPP_
#define _REGISTER_INDIRECT_PARSER_HPP_

#include "OperandParser.hpp"

namespace parsers
{
    class RegisterIndirectParser final : public OperandParser
    {
    public:
        std::shared_ptr<statement::operand_t> parse(std::string operand) override;
        std::shared_ptr<statement::operand_t> parse_jump_instruction(std::string operand) override;

    private:
        bool can_parse(const std::string &operand) const;
        bool can_parse_jump_instruction(const std::string &operand) const;
    };
} // namespace parsers

#endif
