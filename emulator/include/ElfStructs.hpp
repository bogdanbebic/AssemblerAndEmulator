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

        typedef enum RelocationType
        {
            R_16   = 12,
            R_PC16 = 13,
            R_8    = 14,

            R_SECTION16 = 15,
            R_SECTION8  = 16,
        } relocation_type_t;

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
            std::vector<symbol_table_entry_t> symbols;
            size_t offset;
        } section_t;

        symbol_table_entry_t parse_symbol_table_entry(std::string s);
        section_table_entry_t parse_section_table_entry(std::string s);
        relocation_table_entry_t parse_relocation_table_entry(std::string s);
    } // namespace elf
} // namespace linker

#endif
