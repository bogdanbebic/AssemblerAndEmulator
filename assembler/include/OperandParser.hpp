#ifndef _OPERAND_PARSER_HPP_
#define _OPERAND_PARSER_HPP_

#include <memory>
#include <string>

#include "Operand.hpp"

namespace parsers
{
    class OperandParser
    {
    public:
        virtual statement::operand_t parse(std::string operand);
        void set_next(std::shared_ptr<OperandParser> operand_parser);

        OperandParser()                      = default;
        OperandParser(const OperandParser &) = default;
        OperandParser(OperandParser &&)      = default;
        OperandParser &operator=(const OperandParser &) = default;
        OperandParser &operator=(OperandParser &&) = default;
        virtual ~OperandParser()                   = default;

    protected:
        std::shared_ptr<OperandParser> next_{ nullptr };
    };
} // namespace parsers

#endif
