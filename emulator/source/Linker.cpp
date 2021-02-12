#include "Linker.hpp"

#include <algorithm>
#include <fstream>
#include <iostream>

#include "LinkerError.hpp"

size_t linker::Linker::next_section_idx = 0;

void linker::Linker::link(std::vector<std::string> source_file_paths,
                          std::map<std::string, int> section_address_map)
{
    // TODO: link source files according to section_address_map
    for (auto &source_file_path : source_file_paths)
        this->parse_file(source_file_path);

    this->stitch_section_offsets();
    this->add_section_address_offsets(section_address_map);
    this->resolve_relocations();
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
                                          return !entry.is_global ||
                                                 entry.section_index == 0;
                                      }),
                       symbol_table.end());
    // add equ symbols to new symbol table
    for (auto &symbol : symbol_table)
    {
        if (symbol.section_index == 1)
        {
            symbol.section_index         = 0;
            this->symbols[symbol.symbol] = symbol;
        }
    }

    std::vector<elf::section_table_entry_t> section_table = this->parse_section_table(file);
    section_table.erase(std::remove_if(section_table.begin(),
                                       section_table.end(),
                                       [](elf::section_table_entry_t entry) {
                                           return entry.idx < 2;
                                       }),
                        section_table.end());
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

    size_t start_address = 0;
    for (auto section_entry : section_table)
    {
        auto new_section_idx = ++Linker::next_section_idx;
        auto end_address     = start_address + section_entry.size;
        elf::section_t section;
        section.offset      = 0;
        section.descriptor  = section_entry;
        section.object_code = std::vector<emulator::system::byte_t>(
            object_code.begin() + start_address, object_code.begin() + end_address);

        for (auto &relocation : relocation_table)
        {
            if (relocation.offset >= start_address && relocation.offset < end_address)
            {
                relocation.offset -= start_address;
                section.relocations.push_back(relocation);
            }
        }

        for (auto &symbol : symbol_table)
        {
            if (symbol.section_index == section.descriptor.idx)
            {
                symbol.section_index = new_section_idx;
                section.symbols.push_back(symbol);
            }
        }

        section.descriptor.idx = new_section_idx;
        this->sections.push_back(section);
        start_address += section_entry.size;
    }
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

void linker::Linker::stitch_section_offsets()
{
    for (auto &section : this->sections)
    {
        auto section_id = section.descriptor.section;
        if (this->section_sizes.find(section_id) != this->section_sizes.end())
        {
            section.offset = this->section_sizes[section_id];

            // update object code offsets
            for (auto &relocation : section.relocations)
            {
                if (relocation.symbol == section_id)
                {
                    if (relocation.type == elf::R_SECTION16)
                        Linker::add_word(
                            section.object_code, relocation.offset, section.offset);
                    else if (relocation.type == elf::R_SECTION8)
                        Linker::add_byte(
                            section.object_code, relocation.offset, section.offset);
                }
            }

            // update symbol values
            for (auto &symbol : section.symbols)
                symbol.value += section.offset;

            this->section_sizes[section_id] += section.descriptor.size;
        }
        else
        {
            this->section_sizes[section_id] = section.descriptor.size;
        }

        for (auto &symbol : section.symbols)
        {
            if (this->symbols.find(symbol.symbol) == this->symbols.end())
                this->symbols[symbol.symbol] = symbol;
            else
                throw exceptions::LinkerError{ "Double definition of symbol: " +
                                               symbol.symbol };
        }
    }
}

void linker::Linker::add_section_address_offsets(std::map<std::string, int> section_address_map)
{
    for (auto &section : this->sections)
    {
        auto section_id = section.descriptor.section;
        if (section_address_map.find(section_id) != section_address_map.end())
            section.offset += section_address_map[section_id];

        if (this->section_offsets.find(section_id) == this->section_offsets.end())
            this->section_offsets[section_id] = section.offset;
    }
}

void linker::Linker::resolve_relocations()
{
    for (auto &section : this->sections)
    {
        for (auto &relocation : section.relocations)
        {
            switch (relocation.type)
            {
            case elf::R_PC16:
            {
                auto increment = this->symbols[relocation.symbol].value;
                Linker::add_word(section.object_code, relocation.offset, increment);
                break;
            }
            case elf::R_16:
            {
                auto increment   = this->symbols[relocation.symbol].value;
                auto section_idx = this->symbols[relocation.symbol].section_index;
                if (section_idx > 0)
                {
                    auto section_name =
                        this->sections[section_idx - 1].descriptor.section;
                    increment += this->section_offsets[section_name];
                }

                Linker::add_word(section.object_code, relocation.offset, increment);
                break;
            }
            case elf::R_8:
            {
                auto increment   = this->symbols[relocation.symbol].value;
                auto section_idx = this->symbols[relocation.symbol].section_index;
                if (section_idx > 0)
                {
                    auto section_name =
                        this->sections[section_idx - 1].descriptor.section;
                    increment += this->section_offsets[section_name];
                }

                Linker::add_byte(section.object_code, relocation.offset, increment);
                break;
            }
            case elf::R_SECTION16:
            {
                auto increment = this->section_offsets[relocation.symbol];
                Linker::add_word(section.object_code, relocation.offset, increment);
                break;
            }
            case elf::R_SECTION8:
            {
                auto increment = this->section_offsets[relocation.symbol];
                Linker::add_byte(section.object_code, relocation.offset, increment);
                break;
            }

            default:
                break;
            }
        }
    }
}

void linker::Linker::add_byte(std::vector<emulator::system::byte_t> &object_code,
                              size_t offset,
                              emulator::system::byte_t increment)
{
    object_code[offset] += increment;
}

void linker::Linker::add_word(std::vector<emulator::system::byte_t> &object_code,
                              size_t offset,
                              emulator::system::word_t increment)
{
    emulator::system::byte_t low_byte  = increment & 0x00FF;
    emulator::system::byte_t high_byte = (increment & 0xFF00) >> 8;
    object_code[offset] += low_byte;
    object_code[offset + 1] += high_byte;
}
