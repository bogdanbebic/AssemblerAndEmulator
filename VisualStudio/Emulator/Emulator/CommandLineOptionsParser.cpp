#include "CommandLineOptionsParser.h"

#include <sstream>
#include <stdexcept>

void emulator::utility::CommandLineOptionsParser::parse(const int argc, char* argv[])
{
	for (int i = 0; i < argc; i++)
	{
		if (strcmp(argv[i], "-h") == 0 || strcmp(argv[i], "--help") == 0)
		{
			this->option_help_ = true;
		}
		if (strcmp(argv[i], "--bare-memory") == 0)
		{
			this->option_bare_memory_ = true;
			if (++i > argc)
			{
				throw std::invalid_argument{ "No bare memory binary file provided" };
			}

			this->bare_memory_filepath_ = argv[i];
		}

		// TODO: implement --place=<section>@<address> parsing
		// TODO: implement filepath parsing
	}
}

bool emulator::utility::CommandLineOptionsParser::is_help_option() const
{
	return this->option_help_;
}

bool emulator::utility::CommandLineOptionsParser::is_bare_memory_option() const
{
	return this->option_bare_memory_;
}

std::string emulator::utility::CommandLineOptionsParser::bare_memory_filepath() const
{
	return this->bare_memory_filepath_;
}

std::string emulator::utility::CommandLineOptionsParser::help_msg()
{
	std::stringstream ret;
	ret << usage_string << std::endl;
	ret << help_string << std::endl;
	return ret.str();
}
