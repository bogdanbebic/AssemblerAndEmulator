#include "SectionTable.h"

const std::string assembler::SectionTable::undefined_section_entry_name{ "*UND*" };

const std::pair<assembler::SectionTable::key_type, assembler::SectionTable::mapped_type>
    assembler::SectionTable::undefined_section_entry = {
        undefined_section_entry_name, { undefined_section_entry_name, 0, 0 }
    };

assembler::SectionTable::SectionTable()
{
    this->insert(SectionTable::undefined_section_entry);
}

assembler::SectionTable::mapped_type &assembler::SectionTable::at(const key_type &key)
{
    return this->section_table_.at(key);
}

void assembler::SectionTable::insert(const key_type &key)
{
    mapped_type entry = { key, this->next_section_index_++, 0 };
    this->insert({ key, entry });
}

void assembler::SectionTable::update_section_size(const key_type &key, size_t size)
{
    this->section_table_[key].size = size;
}

void assembler::SectionTable::insert(const std::pair<key_type, mapped_type> &entry)
{
    this->section_table_.insert(entry);
}

void assembler::SectionTable::erase(const key_type &key)
{
    this->section_table_.erase(key);
}

std::stringstream assembler::SectionTable::to_school_elf() const
{
    std::stringstream school_elf_stream;
    school_elf_stream << "##########\n";
    school_elf_stream << "# School ELF section table:\n"
                      << "# section,index,size\n";
    for (auto &it : this->section_table_)
    {
        mapped_type section_entry = it.second;
        school_elf_stream << section_entry.section << ',' << section_entry.index
                          << ',' << section_entry.size << '\n';
    }

    school_elf_stream << "##########\n";
    return school_elf_stream;
}
