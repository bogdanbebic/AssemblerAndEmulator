#include "SymbolTable.h"

symbol_table::SymbolTable::mapped_type& symbol_table::SymbolTable::at(const key_type& key)
{
	return this->symbol_table_.at(key);
}

void symbol_table::SymbolTable::insert(std::pair<key_type, mapped_type> entry)
{
	this->symbol_table_.insert(entry);
}

void symbol_table::SymbolTable::erase(const key_type key)
{
	this->symbol_table_.erase(key);
}
