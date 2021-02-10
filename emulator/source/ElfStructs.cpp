#include "ElfStructs.hpp"

#include <iostream>
#include <regex>
#include <stdexcept>

#include "InvalidElf.hpp"

linker::elf::symbol_table_entry_t linker::elf::parse_symbol_table_entry(std::string s)
{
    std::regex re{ "([_a-zA-Z]+),([0-9]+),([0-9]+),([GL])" };
    std::smatch match;
    if (!std::regex_match(s, match, re))
        throw exceptions::InvalidElf{ "Does not contain a school ELF symbol" };

    linker::elf::symbol_table_entry_t ret;
    ret.symbol        = match[1].str();
    ret.value         = std::stoi(match[2].str());
    ret.section_index = std::stoi(match[3].str());
    ret.is_global     = match[4].str()[0] == 'G';
    return ret;
}

linker::elf::section_table_entry_t linker::elf::parse_section_table_entry(std::string s)
{
    std::regex re{ "([\\*_a-zA-Z]+),([0-9]+),([0-9]+)" };
    std::smatch match;
    if (!std::regex_match(s, match, re))
        throw exceptions::InvalidElf{ "Does not contain a school ELF section" };

    linker::elf::section_table_entry_t ret;
    ret.section = match[1].str();
    ret.idx     = std::stoi(match[2].str());
    ret.size    = std::stoi(match[3].str());
    return ret;
}

linker::elf::relocation_table_entry_t linker::elf::parse_relocation_table_entry(std::string s)
{
    std::regex re{ "([_a-zA-Z]+),([0-9]+),([0-9]+),([_A-Z0-9]*)" };
    std::smatch match;
    if (!std::regex_match(s, match, re))
        throw exceptions::InvalidElf{ "Does not contain a school ELF relocation" };

    linker::elf::relocation_table_entry_t ret;
    ret.symbol = match[1].str();
    ret.type   = std::stoi(match[2].str());
    ret.offset = std::stoi(match[3].str());
    return ret;
}
