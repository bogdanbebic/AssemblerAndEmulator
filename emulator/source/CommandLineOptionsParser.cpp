#include "CommandLineOptionsParser.h"

#include <sstream>
#include <stdexcept>

static constexpr char usage_string[] =	"Usage: emulator "
										"[option...] "
										"[--place=<section>@<address>...] "
										"<source_files>...";
static constexpr char help_string[] = 
	"option can be any of:\n"
	"\n"
	"\t-h --help\tprint this message and exit\n"
	"\t--bare-memory <binary_file>\tuse the binary_file for memory\n"
	"\n"
	"Link the source files in an executable and place each section to memory\n"
	"according to the --place parameters. If there is an option selected,\n"
	"ignore the place params and source_files. Starts emulation.";

void emulator::utility::CommandLineOptionsParser::parse(const int argc, char* argv[])
{
	for (int i = 1; i < argc; i++)
	{
		if (strcmp(argv[i], "-h") == 0 || strcmp(argv[i], "--help") == 0)
		{
			this->option_help_ = true;
		}
		else if (strcmp(argv[i], "--bare-memory") == 0)
		{
			this->option_bare_memory_ = true;
			if (++i >= argc)
			{
				throw std::invalid_argument{ "Error: invalid arguments: No bare memory binary file provided" };
			}

			this->bare_memory_filepath_ = argv[i];
		}
		else if (std::regex_match(argv[i], this->match_, this->regex_place_option_))
		{
			std::string section_name = this->match_[1];
			std::string section_address_string = this->match_[2];
			auto section_address = std::stoi(section_address_string);
			
			auto ret_insert = this->section_address_map_.insert({ section_name, section_address });

			bool is_inserted = ret_insert.second;
			if (!is_inserted)
			{
				throw std::invalid_argument{ "Error: invalid arguments: Duplicate section name provided in args" };
			}
		}
		else
		{
			this->source_file_paths_.emplace_back(argv[i]);
		}
	}

	if (!this->is_help_option() && !this->is_bare_memory_option() && this->source_file_paths().empty())
	{
		throw std::invalid_argument{ "Error: invalid arguments: No source files provided" };
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

std::map<std::string, int> emulator::utility::CommandLineOptionsParser::section_address_map() const
{
	return this->section_address_map_;
}

std::vector<std::string> emulator::utility::CommandLineOptionsParser::source_file_paths() const
{
	return this->source_file_paths_;
}
