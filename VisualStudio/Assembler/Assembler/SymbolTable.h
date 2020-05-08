#ifndef SYMBOL_TABLE_H_GUARD
#define SYMBOL_TABLE_H_GUARD

#include <utility>
#include <map>
#include <string>

namespace assembler
{
	class SymbolTable
	{
	public:
		struct SymbolTableEntry
		{
			std::string symbol;
			size_t value;
			size_t section_index;
			bool is_global;
		};
		
		using key_type = std::string;
		using mapped_type = struct SymbolTableEntry;
		
		mapped_type& at(const key_type& key);
		void insert(const std::pair<key_type, mapped_type>& entry);
		void erase(const key_type& key);
	private:
		std::map<key_type, mapped_type> symbol_table_;
	};
}

#endif
