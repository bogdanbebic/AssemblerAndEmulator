#include "RelocationTable.hpp"

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
