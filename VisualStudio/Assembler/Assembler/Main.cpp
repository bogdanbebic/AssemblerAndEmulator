#include <iostream>
#include <fstream>

#include "Parser.h"

int main(int argc, char* argv[])
{
	std::cout << "Hello, World!\n";
	std::ifstream input_file("test_input/test.s");
	parsers::Parser parser;
	parser.parse(input_file);
	std::ofstream output_file("test_input/test.out");
	output_file << parser.to_school_elf().str();
	return 0;
}
