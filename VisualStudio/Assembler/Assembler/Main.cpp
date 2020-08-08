#include <iostream>
#include <fstream>

#include "Parser.h"
#include "LiteralParser.h"

int main(int argc, char* argv[])
{
	std::cout << "argc: " << argc << '\n';
	for (int i = 0; i < argc; i++)
	{
		std::cout << "argv[" << i << "] = " << argv[i] << '\n';
	}
	std::cout << "Hello, World!\n";
	std::ifstream input_file("test_input/test.s");
	parsers::Parser parser;
	parser.parse(input_file);
	std::ofstream output_file("test_input/test.out");
	output_file << parser.to_school_elf().str();

	std::string line;
	
	std::ifstream test_literal_parser_file("test_input/literals.txt");
	std::cout << "\nLiterals test:\n";
	while (std::getline(test_literal_parser_file, line))
	{
		std::cout << parsers::LiteralParser::parse(line) << '\n';
	}

	std::ifstream test_literal_expr_parser_file("test_input/literals-expr.txt");
	std::cout << "\nLiterals expressions test:\n";
	while (std::getline(test_literal_expr_parser_file, line))
	{
		std::cout << parsers::LiteralParser::evaluate_expression(line) << '\n';
	}
	
	return 0;
}
