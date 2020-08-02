#include "LiteralParser.h"
#include <sstream>
#include <ios>
#include "LiteralParsingException.h"

std::regex parsers::LiteralParser::char_literal_regex_{ "^'.'$" };
std::regex parsers::LiteralParser::decimal_literal_regex_{ "^[+-]?[1-9][0-9]*$" };
std::regex parsers::LiteralParser::octal_literal_regex_{ "^[+-]?0[0-7]*$" }; // * instead of + is a hack for parsing 0
std::regex parsers::LiteralParser::hex_literal_regex_{ "^[+-]?0x[0-9a-f]+$" };

std::cmatch parsers::LiteralParser::match_{};

bool parsers::LiteralParser::is_literal(const std::string& string)
{
	return is_char_literal(string)
		|| is_decimal_literal(string)
		|| is_octal_literal(string)
		|| is_hex_literal(string);
}

int parsers::LiteralParser::parse(const std::string& string)
{
	if (is_char_literal(string))
		return parse_char_literal(string);
	if (is_decimal_literal(string))
		return parse_decimal_literal(string);
	if (is_octal_literal(string))
		return parse_octal_literal(string);
	if (is_hex_literal(string))
		return parse_hex_literal(string);

	throw LiteralParsingException();
}

bool parsers::LiteralParser::is_char_literal(const std::string& string)
{
	return std::regex_match(string.c_str(), match_, char_literal_regex_);
}

bool parsers::LiteralParser::is_decimal_literal(const std::string& string)
{
	return std::regex_match(string.c_str(), match_, decimal_literal_regex_);
}

bool parsers::LiteralParser::is_octal_literal(const std::string& string)
{
	return std::regex_match(string.c_str(), match_, octal_literal_regex_);
}

bool parsers::LiteralParser::is_hex_literal(const std::string& string)
{
	return std::regex_match(string.c_str(), match_, hex_literal_regex_);
}

int parsers::LiteralParser::parse_char_literal(const std::string& string)
{
	return string[1];
}

int parsers::LiteralParser::parse_decimal_literal(const std::string& string)
{
	std::stringstream string_stream;
	string_stream << string;
	int decimal_literal;
	string_stream >> std::dec >> decimal_literal;
	return decimal_literal;
}

int parsers::LiteralParser::parse_octal_literal(const std::string& string)
{
	std::stringstream string_stream;
	string_stream << string;
	int octal_literal;
	string_stream >> std::oct >> std::showbase >> octal_literal;
	return octal_literal;
}

int parsers::LiteralParser::parse_hex_literal(const std::string& string)
{
	std::stringstream string_stream;
	string_stream << string;
	int hex_literal;
	string_stream >> std::hex >> std::showbase >> hex_literal;
	return hex_literal;
}
