#include "CommandLineOptionsParser.h"

#include <sstream>
#include <stdexcept>

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
			if (++i > argc)
			{
				throw std::invalid_argument{ "No bare memory binary file provided" };
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
				throw std::invalid_argument{ "Duplicate section name provided in args" };
			}
		}
		else
		{
			this->source_file_paths_.emplace_back(argv[i]);
		}
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
