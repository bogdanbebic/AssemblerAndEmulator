#include "RelocationTable.hpp"

#include <sstream>

#include "SymbolTable.hpp"

assembler::RelocationTable::RelocationTable(std::shared_ptr<SymbolTable> symbol_table)
    : symbol_table_(symbol_table)
{
    // empty body
}

void assembler::RelocationTable::add_equ_relocation(const std::string &equ_entry_key,
                                                    const std::string &relocation_entry_key)
{
    this->equ_relocations_.insert({ equ_entry_key, relocation_entry_key });
}

std::stringstream assembler::RelocationTable::to_school_elf() const
{
    std::stringstream school_elf_stream;
    school_elf_stream << "##########\n";
    school_elf_stream << "# School ELF relocation table:\n"
                      << "# symbol,type,offset\n";

    for (auto &relocation_entry : this->relocation_table_)
    {
        school_elf_stream << relocation_entry.symbol << ',' << relocation_entry.type
                          << ',' << relocation_entry.offset << '\n';
    }

    school_elf_stream << "##########\n";
    return school_elf_stream;
}
