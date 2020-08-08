#ifndef SYMBOL_TABLE_H_GUARD
#define SYMBOL_TABLE_H_GUARD

#include <utility>
#include <map>
#include <string>
#include <sstream>

namespace assembler
{
	class SymbolTable
	{
	public:
		struct SymbolTableEntry
		{
			std::string symbol = "";
			size_t value = 0;
			size_t section_index = 0;
			bool is_global = false;
		};
		
		using key_type = std::string;
		using mapped_type = struct SymbolTableEntry;
		
		mapped_type& at(const key_type& key);
		void insert(const std::pair<key_type, mapped_type>& entry);
		void erase(const key_type& key);
		void make_global(const key_type& key);
		void make_extern(const key_type& key);

		std::stringstream to_school_elf() const;
	private:
		std::map<key_type, mapped_type> symbol_table_;
	};
}

#endif
