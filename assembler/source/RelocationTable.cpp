#include "RelocationTable.hpp"

#include <algorithm>
#include <iostream>
#include <sstream>

#include "ObjectCodeArray.hpp"
#include "SectionTable.hpp"
#include "SymbolTable.hpp"
#include "UndefinedSymbolReference.hpp"

assembler::RelocationTable::RelocationTable(std::shared_ptr<SymbolTable> symbol_table,
                                            std::shared_ptr<SectionTable> section_table,
                                            std::shared_ptr<ObjectCodeArray> object_code)
    : symbol_table_(symbol_table), section_table_(section_table), object_code_(object_code)
{
    // empty body
}

void assembler::RelocationTable::insert(relocation_table_entry_t entry)
{
    this->relocation_table_.push_back(entry);
}

void assembler::RelocationTable::add_equ_relocation(const std::string &equ_entry_key,
                                                    const std::string &relocation_entry_key)
{
    this->equ_relocations_.insert({ equ_entry_key, relocation_entry_key });
}

void assembler::RelocationTable::cleanup_equ_relocations()
{
    for (auto &relocation_entry : this->relocation_table_)
    {
        auto equ_relocation_entry = this->equ_relocations_.find(relocation_entry.symbol);
        if (equ_relocation_entry != this->equ_relocations_.end())
        {
            relocation_entry.symbol = equ_relocation_entry->second;
        }
    }
}

void assembler::RelocationTable::cleanup_forward_references()
{
    // remove local PC relative relocation entries
    this->relocation_table_.erase(
        std::remove_if(this->relocation_table_.begin(),
                       this->relocation_table_.end(),
                       [this](assembler::RelocationTable::relocation_table_entry_t entry) {
                           if (entry.type == R_PC16 &&
                               this->symbol_table_->is_defined(entry.symbol))
                           {
                               this->object_code_->increment_word(
                                   entry.offset,
                                   this->symbol_table_->at(entry.symbol).value);
                               return true;
                           }

                           return false;
                       }),
        this->relocation_table_.end());

    // cleanup local forward references
    for (auto &entry : this->relocation_table_)
    {
        if (this->symbol_table_->is_defined(entry.symbol) &&
            !this->symbol_table_->is_global(entry.symbol))
        {
            if (entry.type == R_16)
            {
                this->object_code_->increment_word(
                    entry.offset, this->symbol_table_->at(entry.symbol).value);
                entry.type   = R_SECTION16;
                entry.symbol = this->section_table_->section_name(
                    this->symbol_table_->at(entry.symbol).section_index);
            }

            if (entry.type == R_8)
            {
                this->object_code_->increment_byte(
                    entry.offset, this->symbol_table_->at(entry.symbol).value);
                entry.type   = R_SECTION8;
                entry.symbol = this->section_table_->section_name(
                    this->symbol_table_->at(entry.symbol).section_index);
            }
        }
    }

    // remove equ section relocations
    this->relocation_table_.erase(
        std::remove_if(this->relocation_table_.begin(),
                       this->relocation_table_.end(),
                       [this](assembler::RelocationTable::relocation_table_entry_t entry) {
                           return entry.symbol == assembler::SectionTable::equ_section_entry_name;
                       }),
        this->relocation_table_.end());

    // check for undefined references
    auto undefined_references_exist = false;
    for (auto &entry : this->relocation_table_)
    {
        if (entry.type != R_SECTION16 && entry.type != R_SECTION8 &&
            !this->symbol_table_->is_global(entry.symbol))
        {
            undefined_references_exist = true;
            std::cerr << "Undefined symbol: " << entry.symbol << std::endl;
        }
    }

    if (undefined_references_exist)
        throw UndefinedSymbolReference{};
}

std::stringstream assembler::RelocationTable::to_school_elf() const
{
    const std::map<relocation_type_t, std::string> relocation_type_descriptions = {
        { R_16, "R_16" },
        { R_PC16, "R_PC16" },
        { R_8, "R_8" },

        { R_SECTION16, "R_SECTION16" },
        { R_SECTION8, "R_SECTION8" },
    };

    std::stringstream school_elf_stream;
    school_elf_stream << "##########\n";
    school_elf_stream << "# School ELF relocation table:\n"
                      << "# symbol,type,offset,type_string\n";

    for (auto &relocation_entry : this->relocation_table_)
    {
        school_elf_stream << relocation_entry.symbol << ',' << relocation_entry.type
                          << ',' << relocation_entry.offset << ','
                          << relocation_type_descriptions.at(relocation_entry.type)
                          << '\n';
    }

    school_elf_stream << "##########\n";
    return school_elf_stream;
}
