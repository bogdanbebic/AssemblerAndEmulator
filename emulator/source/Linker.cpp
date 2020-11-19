#include "Linker.hpp"

void linker::Linker::link(std::vector<std::string> source_file_paths,
                          std::map<std::string, int> section_address_map)
{
    // TODO: link source files according to section_address_map
}

std::vector<emulator::system::byte_t> linker::Linker::memory_contents() const
{
    return this->memory_contents_;
}
