#ifndef LINE_COMMENT_STRIPPER_H_GUARD
#define LINE_COMMENT_STRIPPER_H_GUARD

#include <string>
#include <regex>

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
}

#endif
