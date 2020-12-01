#include <fstream>
#include <iostream>

#include "CommandLineOptionsParser.hpp"
#include "Emulator.hpp"
#include "Linker.hpp"
#include "Typedefs.hpp"

int main(int argc, char *argv[])
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

    emulator::system::Emulator emu;

    if (cmd_parser.is_bare_memory_option())
    {
        std::ifstream memory_file{ cmd_parser.bare_memory_filepath(), std::ifstream::binary };
        std::vector<emulator::system::byte_t> contents{
            std::istreambuf_iterator<char>{ memory_file }, std::istreambuf_iterator<char>{}
        };

        emu.load_memory(contents);
    }
    else
    {
        linker::Linker linker;
        try
        {
            std::cout << "Linking source files..." << std::endl;
            linker.link(cmd_parser.source_file_paths(), cmd_parser.section_address_map());
            if (cmd_parser.is_link_only_option())
            {
                std::ofstream memory_file{ cmd_parser.link_only_filepath(),
                                           std::ofstream::binary };
                auto linked_memory_contents = linker.memory_contents();
                std::copy(linked_memory_contents.begin(),
                          linked_memory_contents.end(),
                          std::ostreambuf_iterator<char>{ memory_file });
                return 0;
            }

            emu.load_memory(linker.memory_contents());
        }
        catch (std::exception &ex)
        {
            std::cerr << ex.what() << std::endl;
            return 0;
        }
    }

    std::cout << "Emulator started!" << std::endl;
    emu.emulate();
    std::cout << "Emulator finished!" << std::endl;

    return 0;
}
