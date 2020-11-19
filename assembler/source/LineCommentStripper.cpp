#include "LineCommentStripper.hpp"

std::string parsers::LineCommentStripper::strip_line_comment(std::string line)
{
    if (std::regex_match(line.c_str(), this->match_, this->regex_))
    {
        return this->match_[1].str();
    }

    return line;
}
