#ifndef SECTION_TABLE_H_GUARD
#define SECTION_TABLE_H_GUARD
#include <map>
#include <string>

namespace assembler
{
	class SectionTable
	{
	public:
		struct SectionTableEntry
		{
			std::string section;
			size_t index;
			size_t size;
		};

		using key_type = std::string;
		using mapped_type = struct SectionTableEntry;

		mapped_type& at(const key_type& key);
		void insert(std::pair<key_type, mapped_type> entry);
		void erase(key_type key);
	private:
		std::map<key_type, mapped_type> symbol_table_;
	};

}

#endif
