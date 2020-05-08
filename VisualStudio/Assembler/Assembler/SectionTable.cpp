#include "SectionTable.h"

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
