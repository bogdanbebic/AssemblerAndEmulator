#include <fstream>
#include <iostream>
#include <stdexcept>

#include "CommandOptions.hpp"
#include "Parser.hpp"

int main(int argc, char *argv[])
{
    try
    {
        CommandOptions command_options{ argc, argv };
        if (command_options.is_help_option_set())
        {
            std::cout << command_options.help_message();
            return 0;
        }

        // TODO: delete
        std::cout << "Input file: " << command_options.input_file_name() << "\n";
        std::cout << "Output file: " << command_options.output_file_name() << "\n";

        std::ifstream input_file{ command_options.input_file_name() };
        parsers::Parser parser;
        parser.parse(input_file);

        std::ofstream output_file{ command_options.output_file_name() };
        output_file << parser.to_school_elf().str();
    }
    catch (std::invalid_argument &ex)
    {
        std::cout << ex.what() << std::endl;
    }
    catch (std::exception &ex)
    {
        std::cerr << "Error: " << ex.what() << std::endl;
    }

    return 0;
}
