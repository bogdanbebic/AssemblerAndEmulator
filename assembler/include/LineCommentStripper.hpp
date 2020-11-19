#ifndef _LINE_COMMENT_STRIPPER_HPP_
#define _LINE_COMMENT_STRIPPER_HPP_

#include <regex>
#include <string>

namespace parsers
{
    class LineCommentStripper
    {
    public:
        std::string strip_line_comment(std::string line);

    private:
        std::regex regex_{ "^([^#]*)(#.*)?$" };
        std::cmatch match_;
    };
} // namespace parsers

#endif
