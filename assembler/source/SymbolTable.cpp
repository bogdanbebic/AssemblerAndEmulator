#include "SymbolTable.hpp"

#include <algorithm>
#include <stdexcept>

assembler::SymbolTable::mapped_type &assembler::SymbolTable::at(const key_type &key)
{
    return this->symbol_table_.at(key);
}

void assembler::SymbolTable::insert(const std::pair<key_type, mapped_type> &entry)
{
    if (this->symbol_table_.find(entry.first) == this->symbol_table_.end())
    {
        this->symbol_table_.insert(entry);
    }
    else
    {
        this->symbol_table_[entry.first].section_index = entry.second.section_index;
        this->symbol_table_[entry.first].value         = entry.second.value;
    }
}

void assembler::SymbolTable::erase(const key_type &key)
{
    this->symbol_table_.erase(key);
}

void assembler::SymbolTable::make_global(const key_type &key)
{
    if (this->symbol_table_.find(key) != this->symbol_table_.end())
    {
        this->symbol_table_.at(key).is_global = true;
    }
    else
    {
        this->symbol_table_[key] = { key, 0, 0, true };
    }
}

void assembler::SymbolTable::make_extern(const key_type &key)
{
    if (this->symbol_table_.find(key) == this->symbol_table_.end())
    {
        this->symbol_table_[key] = { key, 0, 0, true };
    }
    else
    {
        throw std::invalid_argument{ "Cannot be extern, already defined" };
    }
}

void assembler::SymbolTable::make_declaration(const key_type &key)
{
    if (this->symbol_table_.find(key) == this->symbol_table_.end())
    {
        this->symbol_table_[key] = { key, 0, 0, false };
    }
}

std::stringstream assembler::SymbolTable::to_school_elf() const
{
    std::stringstream school_elf_stream;
    school_elf_stream << "##########\n";
    school_elf_stream << "# School ELF symbol table:\n"
                      << "# symbol,value,section_index,is_global(G/L)\n";
    for (auto &it : this->symbol_table_)
    {
        mapped_type symbol_entry = it.second;
        school_elf_stream << symbol_entry.symbol << ',' << symbol_entry.value
                          << ',' << symbol_entry.section_index << ','
                          << (symbol_entry.is_global ? 'G' : 'L') << '\n';
    }

    school_elf_stream << "##########\n";
    return school_elf_stream;
}
