#include <iostream>
#include <fstream>
#include <stdexcept>

#include "CommandOptions.h"

int main(int argc, char* argv[])
{
	try
	{
		CommandOptions command_options{ argc, argv };
		if (command_options.is_help_option_set())
		{
			std::cout << command_options.help_message();
			return 0;
		}

		std::cout << "Input file: " << command_options.input_file_name() << "\n";
		std::cout << "Output file: " << command_options.output_file_name() << "\n";
	}
	catch (std::invalid_argument& ex)
	{
		std::cout << ex.what() << std::endl;
	}
	catch (std::exception & ex)
	{
		std::cerr << "Error: " << ex.what() << std::endl;
	}
	
	return 0;
}
