#ifndef _ELF_STRUCTS_HPP_
#define _ELF_STRUCTS_HPP_

#include <string>
#include <vector>

#include "Typedefs.hpp"

namespace linker
{
    namespace elf
    {
        typedef struct SymbolTableEntry
        {
            std::string symbol;
            emulator::system::word_t value;
            size_t section_index;
            bool is_global;
        } symbol_table_entry_t;

        typedef struct SectionTableEntry
        {
            std::string section;
            size_t idx;
            size_t size;
        } section_table_entry_t;

        using relocation_type_t = int;
        typedef struct RelocationTableEntry
        {
            std::string symbol;
            relocation_type_t type;
            size_t offset;
        } relocation_table_entry_t;

        typedef struct Section
        {
            section_table_entry_t descriptor;
            std::vector<emulator::system::byte_t> object_code;
            std::vector<relocation_table_entry_t> relocations;
        } section_t;

        symbol_table_entry_t parse_symbol_table_entry(std::string s);
        section_table_entry_t parse_section_table_entry(std::string s);
        relocation_table_entry_t parse_relocation_table_entry(std::string s);
    } // namespace elf
} // namespace linker

#endif
