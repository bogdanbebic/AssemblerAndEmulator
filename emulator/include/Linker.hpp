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

        std::vector<emulator::system::byte_t> memory_contents_;
    };
} // namespace linker

#endif
