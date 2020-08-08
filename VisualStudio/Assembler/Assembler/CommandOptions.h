#ifndef COMMAND_OPTIONS_H_GUARD
#define COMMAND_OPTIONS_H_GUARD

#include <string>

class CommandOptions
{
public:
	CommandOptions(int argc, char* argv[]);

	std::string help_message() const;

	bool is_help_option_set() const;
	
	std::string input_file_name() const;
	std::string output_file_name() const;
private:
	bool help_flag_ = false;
	std::string input_file_name_;
	std::string output_file_name_;
};

#endif
