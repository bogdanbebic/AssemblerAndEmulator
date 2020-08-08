#include "CommandOptions.h"

#include <stdexcept>

#ifndef _WIN32

#include <unistd.h>

#endif


CommandOptions::CommandOptions(int argc, char* argv[])
{
#ifdef _WIN32
	switch (argc)
	{
	case 2:
		// only input argument
		this->input_file_name_ = argv[1];
		this->output_file_name_ = this->input_file_name() + ".ss_elf";
		break;
	case 3:
		// both input and output argument
		this->input_file_name_ = argv[1];
		this->output_file_name_ = argv[2];
		break;
	default:
		throw std::invalid_argument{
			std::string{"Error: invalid arguments\n"}
			+ this->help_message()
		};
	}
#else
	// LINUX
	// TODO: implement
#endif
}

std::string CommandOptions::help_message() const
{
#ifdef _WIN32
	return std::string{
		"Usage: assembler <input_file> [<output_file>]\n"
	};
#else
	// LINUX
	return std::string{
		"Usage: assembler [-h] [-o <output_file>] <input_file>\n"
		"Options:\n"
		"\t-h - print this message and quit\n"
	};
#endif
}

bool CommandOptions::is_help_option_set() const
{
#ifdef _WIN32
	return false;
#else
	// LINUX
	// TODO: implement
	return false;
#endif
}

std::string CommandOptions::input_file_name() const
{
	return this->input_file_name_;
}

std::string CommandOptions::output_file_name() const
{
	return this->output_file_name_;
}
