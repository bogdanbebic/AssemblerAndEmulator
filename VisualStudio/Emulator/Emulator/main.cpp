#include <iostream>
#include <fstream>

#include "Typedefs.h"
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

	if (cmd_parser.is_bare_memory_option())
	{
		std::ifstream memory_file{cmd_parser.bare_memory_filepath(), std::ifstream::binary };
		std::vector<emulator::system::byte_t> contents{ std::istreambuf_iterator<char>{ memory_file },
														std::istreambuf_iterator<char>{} };
		// TODO: load contents to memory
	}
	else
	{
		// TODO: link source files
	}
	
	std::cout << "Emulator started!" << std::endl;

	return 0;
}
