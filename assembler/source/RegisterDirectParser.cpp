#include "RegisterDirectParser.hpp"

#include <regex>

std::shared_ptr<statement::operand_t> parsers::RegisterDirectParser::parse(std::string operand)
{
    if (!this->can_parse(operand))
        return OperandParser::parse(operand);

    auto ret             = std::make_shared<statement::operand_t>();
    ret->addressing_mode = statement::REGISTER;

    if (operand[operand.size() - 1] == 'h' || operand[operand.size() - 1] == 'l')
    {
        ret->low_high_byte_exists = 1;
        if (operand[operand.size() - 1] == 'h')
            ret->low_high_byte = 1;
        operand = operand.substr(0, operand.size() - 1);
    }

    const std::regex regex{ "^%r([0-7])$" };
    std::smatch match;

    if (std::regex_match(operand, match, regex))
        ret->register_index = std::stoi(match[1].str());
    else if (operand == "%pc")
        ret->register_index = 7;
    else if (operand == "%sp")
        ret->register_index = 6;
    else if (operand == "%psw")
        ret->register_index = 0xF;

    return ret;
}

std::shared_ptr<statement::operand_t>
parsers::RegisterDirectParser::parse_jump_instruction(std::string operand)
{
    if (!this->can_parse_jump_instruction(operand))
        return OperandParser::parse_jump_instruction(operand);

    auto ret             = std::make_shared<statement::operand_t>();
    ret->addressing_mode = statement::REGISTER;

    if (operand[operand.size() - 1] == 'h' || operand[operand.size() - 1] == 'l')
    {
        ret->low_high_byte_exists = 1;
        if (operand[operand.size() - 1] == 'h')
            ret->low_high_byte = 1;
        operand = operand.substr(0, operand.size() - 1);
    }

    const std::regex regex{ "^\\*%r([0-7])$" };
    std::smatch match;

    if (std::regex_match(operand, match, regex))
        ret->register_index = std::stoi(match[1].str());
    else if (operand == "*%pc")
        ret->register_index = 7;
    else if (operand == "*%sp")
        ret->register_index = 6;
    else if (operand == "*%psw")
        ret->register_index = 0xF;

    return ret;
}

bool parsers::RegisterDirectParser::can_parse(const std::string &operand) const
{
    const std::regex register_direct_regex{ "^%(r[0-7]|pc|sp|psw)[hl]?$" };
    return std::regex_match(operand, register_direct_regex);
}

bool parsers::RegisterDirectParser::can_parse_jump_instruction(const std::string &operand) const
{
    const std::regex register_direct_regex{ "^\\*%(r[0-7]|pc|sp|psw)[hl]?$" };
    return std::regex_match(operand, register_direct_regex);
}
