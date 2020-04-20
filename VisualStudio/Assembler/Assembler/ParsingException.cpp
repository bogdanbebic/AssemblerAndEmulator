#include "ParsingException.h"

char const* parsers::ParsingException::what() const
{
	return "Invalid label: label must be an identifier followed by a colon.";
}
