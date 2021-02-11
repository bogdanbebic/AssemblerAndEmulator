#ifndef _LINKER_HPP_
#define _LINKER_HPP_

#include <map>
#include <string>
#include <vector>

#include "ElfStructs.hpp"
#include "Typedefs.hpp"

namespace linker
{
    class Linker
    {
    public:
        void link(std::vector<std::string> source_file_paths,
                  std::map<std::string, int> section_address_map);

        std::vector<emulator::system::byte_t> memory_contents() const;

    private:
        void parse_file(const std::string &filepath);

        std::vector<elf::symbol_table_entry_t> parse_symbol_table(std::istream &is);
        std::vector<elf::section_table_entry_t> parse_section_table(std::istream &is);
        std::vector<emulator::system::byte_t> parse_object_code(std::istream &is, size_t size);
        std::vector<elf::relocation_table_entry_t> parse_relocation_table(std::istream &is);

        void stitch_section_offsets();
        void add_section_address_offsets(std::map<std::string, int> section_address_map);
        void resolve_relocations();

        static void add_byte(std::vector<emulator::system::byte_t> &object_code,
                             size_t offset,
                             emulator::system::byte_t increment);
        static void add_word(std::vector<emulator::system::byte_t> &object_code,
                             size_t offset,
                             emulator::system::word_t increment);

        static size_t next_section_idx;

        std::map<std::string, elf::symbol_table_entry_t> symbols;

        std::vector<elf::section_t> sections;
        std::map<std::string, size_t> section_offsets;
        std::map<std::string, size_t> section_sizes;

        std::vector<emulator::system::byte_t> memory_contents_;
    };
} // namespace linker

#endif
