#include "Linker.hpp"

#include <algorithm>
#include <fstream>
#include <iostream>

void linker::Linker::link(std::vector<std::string> source_file_paths,
                          std::map<std::string, int> section_address_map)
{
    // TODO: link source files according to section_address_map
    for (auto &source_file_path : source_file_paths)
        this->parse_file(source_file_path);
}

std::vector<emulator::system::byte_t> linker::Linker::memory_contents() const
{
    return this->memory_contents_;
}

void linker::Linker::parse_file(const std::string &filepath)
{
    std::ifstream file{ filepath, std::ifstream::binary };

    std::vector<elf::symbol_table_entry_t> symbol_table = this->parse_symbol_table(file);
    symbol_table.erase(std::remove_if(symbol_table.begin(),
                                      symbol_table.end(),
                                      [](elf::symbol_table_entry_t entry) {
                                          return !entry.is_global;
                                      }),
                       symbol_table.end());

    std::vector<elf::section_table_entry_t> section_table = this->parse_section_table(file);
    std::sort(section_table.begin(),
              section_table.end(),
              [](elf::section_table_entry_t entry1, elf::section_table_entry_t entry2) {
                  return entry1.idx < entry2.idx;
              });

    size_t object_code_size = 0;
    for (auto &entry : section_table)
        object_code_size += entry.size;

    std::vector<emulator::system::byte_t> object_code =
        this->parse_object_code(file, object_code_size);

    std::vector<elf::relocation_table_entry_t> relocation_table =
        this->parse_relocation_table(file);

    // std::cout << "Parsing file " << filepath << std::endl;
    std::cout << "SYMBOL:\n";
    for (auto &entry : symbol_table)
        std::cout << entry.symbol << "-" << entry.value << "-"
                  << entry.section_index << "-" << entry.is_global << std::endl;
    std::cout << "SECTION:\n";
    for (auto &entry : section_table)
        std::cout << entry.section << "-" << entry.idx << "-" << entry.size << std::endl;
    std::cout << "RELOCATION:\n";
    for (auto &entry : relocation_table)
        std::cout << entry.symbol << "-" << entry.type << "-" << entry.offset << std::endl;
}

std::vector<linker::elf::symbol_table_entry_t> linker::Linker::parse_symbol_table(std::istream &is)
{
    std::vector<elf::symbol_table_entry_t> ret;
    std::string line;
    std::getline(is, line); // get opening #'s
    while (std::getline(is, line))
    {
        if (line == "##########") // closing #'s
            break;

        if (line[0] == '#')
            continue;

        ret.push_back(elf::parse_symbol_table_entry(line));
    }

    return ret;
}

std::vector<linker::elf::section_table_entry_t>
linker::Linker::parse_section_table(std::istream &is)
{
    std::vector<elf::section_table_entry_t> ret;
    std::string line;
    std::getline(is, line); // get opening #'s
    while (std::getline(is, line))
    {
        if (line == "##########") // closing #'s
            break;

        if (line[0] == '#')
            continue;

        ret.push_back(elf::parse_section_table_entry(line));
    }

    return ret;
}

std::vector<emulator::system::byte_t> linker::Linker::parse_object_code(std::istream &is, size_t size)
{
    std::string line;

    // get opening #'s
    std::getline(is, line);
    // get # line
    std::getline(is, line);

    // read object code
    std::vector<emulator::system::byte_t> vec;
    vec.reserve(size);
    for (size_t i = 0; i < size; i++)
        vec.push_back(is.get());

    // get newline before closing #'s
    std::getline(is, line);
    // get closing #'s
    std::getline(is, line);
    return vec;
}

std::vector<linker::elf::relocation_table_entry_t>
linker::Linker::parse_relocation_table(std::istream &is)
{
    std::vector<elf::relocation_table_entry_t> ret;
    std::string line;
    std::getline(is, line); // get opening #'s
    while (std::getline(is, line))
    {
        if (line == "##########") // closing #'s
            break;

        if (line[0] == '#')
            continue;

        ret.push_back(elf::parse_relocation_table_entry(line));
    }

    return ret;
}
