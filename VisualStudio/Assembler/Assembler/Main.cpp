#include <iostream>
#include <fstream>

#include "Parser.h"
#include "LiteralParser.h"

int main(int argc, char* argv[])
{
	std::cout << "Hello, World!\n";
	std::ifstream input_file("test_input/test.s");
	parsers::Parser parser;
	parser.parse(input_file);
	std::ofstream output_file("test_input/test.out");
	output_file << parser.to_school_elf().str();

	std::ifstream test_literal_parser_file("test_input/literals.txt");
	std::string line;
	std::cout << "\nLiterals test:\n";
	while (std::getline(test_literal_parser_file, line))
	{
		std::cout << parsers::LiteralParser::parse(line) << '\n';
	}
	
	return 0;
}
