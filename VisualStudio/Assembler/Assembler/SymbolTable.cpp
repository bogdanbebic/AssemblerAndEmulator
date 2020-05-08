#include "SymbolTable.h"

assembler::SymbolTable::mapped_type& assembler::SymbolTable::at(const key_type& key)
{
	return this->symbol_table_.at(key);
}

void assembler::SymbolTable::insert(const std::pair<key_type, mapped_type>& entry)
{
	this->symbol_table_.insert(entry);
}

void assembler::SymbolTable::erase(const key_type& key)
{
	this->symbol_table_.erase(key);
}
