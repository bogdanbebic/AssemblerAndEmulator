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

		static const std::string undefined_section_entry_name;
		static const std::pair<key_type, mapped_type> undefined_section_entry;
		
		SectionTable();
		
		mapped_type& at(const key_type& key);
		void insert(const key_type& key);
		void update_section_size(const key_type& key, size_t size);
		void erase(const key_type& key);
	private:
		void insert(const std::pair<key_type, mapped_type>& entry);
		
		std::map<key_type, mapped_type> section_table_;
		size_t next_section_index_ = 1;
	};

}

#endif
