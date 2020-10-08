#ifndef _COMMAND_LINE_OPTIONS_H_
#define _COMMAND_LINE_OPTIONS_H_
#include <string>

namespace emulator
{
	namespace utility
	{
		class CommandLineOptionsParser
		{
		public:
			void parse(int argc, char* argv[]);
			
			bool is_help_option() const;
			bool is_bare_memory_option() const;
			std::string bare_memory_filepath() const;
			static std::string help_msg();
		private:
			bool option_help_ = false;
			bool option_bare_memory_ = false;
			std::string bare_memory_filepath_;

			
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
		};
	}
}

#endif
