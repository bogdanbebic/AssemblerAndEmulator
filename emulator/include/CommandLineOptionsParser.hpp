#ifndef _COMMAND_LINE_OPTIONS_HPP_
#define _COMMAND_LINE_OPTIONS_HPP_

#include <map>
#include <regex>
#include <string>
#include <vector>

namespace emulator
{
    namespace utility
    {
        class CommandLineOptionsParser
        {
        public:
            void parse(int argc, char *argv[]);

            bool is_help_option() const;
            bool is_bare_memory_option() const;
            std::string bare_memory_filepath() const;
            bool is_link_only_option() const;
            std::string link_only_filepath() const;
            static std::string help_msg();
            std::map<std::string, int> section_address_map() const;
            std::vector<std::string> source_file_paths() const;

        private:
            bool option_help_ = false;

            bool option_bare_memory_ = false;
            std::string bare_memory_filepath_;

            bool option_link_only_ = false;
            std::string link_only_filepath_;

            std::map<std::string, int> section_address_map_;
            std::vector<std::string> source_file_paths_;

            std::regex regex_place_option_{ "^--place=(\\w+)@(\\w+)$" };
            std::cmatch match_;
        };
    } // namespace utility
} // namespace emulator

#endif
