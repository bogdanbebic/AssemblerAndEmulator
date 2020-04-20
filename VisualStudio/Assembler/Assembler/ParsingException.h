#ifndef PARSING_EXCEPTION_H_GUARD
#define PARSING_EXCEPTION_H_GUARD

#include <exception>

namespace parsers
{

	class ParsingException : public std::exception
	{
	public:
		char const* what() const override;
	};

}

#endif
