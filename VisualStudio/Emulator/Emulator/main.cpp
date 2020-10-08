#include <iostream>

#include "CommandLineOptionsParser.h"

int main(int argc, char* argv[])
{
	emulator::utility::CommandLineOptionsParser cmd_parser;
	try
	{
		cmd_parser.parse(argc, argv);
	}
	catch (std::invalid_argument &ex)
	{
		std::cerr << ex.what();
		std::cout << emulator::utility::CommandLineOptionsParser::help_msg();
		return 0;
	}
	
	std::cout << "-h = --help   =" << cmd_parser.is_help_option() << std::endl;
	std::cout << "--bare-memory =" << cmd_parser.is_bare_memory_option() << std::endl;

	if (cmd_parser.is_help_option())
	{
		std::cout << emulator::utility::CommandLineOptionsParser::help_msg();
		return 0;
	}
	
	std::cout << "Emulator started!" << std::endl;

	return 0;
}
