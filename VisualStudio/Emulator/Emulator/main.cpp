#include <iostream>

#include "CommandLineOptionsParser.h"

int main(int argc, char* argv[])
{
	emulator::utility::CommandLineOptionsParser cmd_parser;
	try
	{
		cmd_parser.parse(argc, argv);
	}
	catch (std::exception &ex)
	{
		std::cerr << ex.what() << std::endl;
		std::cout << emulator::utility::CommandLineOptionsParser::help_msg();
		return 0;
	}

	if (cmd_parser.is_help_option())
	{
		std::cout << emulator::utility::CommandLineOptionsParser::help_msg();
		return 0;
	}
	
	std::cout << "Emulator started!" << std::endl;

	return 0;
}
