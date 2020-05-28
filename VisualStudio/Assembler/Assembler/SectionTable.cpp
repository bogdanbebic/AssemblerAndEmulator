#include "SectionTable.h"

const std::string assembler::SectionTable::undefined_section_entry_name{ "*UND*" };

const std::pair<
	assembler::SectionTable::key_type,
	assembler::SectionTable::mapped_type
> assembler::SectionTable::undefined_section_entry = 
{
	undefined_section_entry_name,
	{
		undefined_section_entry_name,
		0,
		0
	}
};

assembler::SectionTable::SectionTable()
{
	this->insert(SectionTable::undefined_section_entry);
}

assembler::SectionTable::mapped_type& assembler::SectionTable::at(const key_type& key)
{
	return this->section_table_.at(key);
}

void assembler::SectionTable::insert(const std::pair<key_type, mapped_type>& entry)
{
	this->section_table_.insert(entry);
}

void assembler::SectionTable::erase(const key_type& key)
{
	this->section_table_.erase(key);
}
