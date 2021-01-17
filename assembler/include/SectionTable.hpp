#ifndef _SECTION_TABLE_HPP_
#define _SECTION_TABLE_HPP_

#include <map>
#include <sstream>
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

        using key_type    = std::string;
        using mapped_type = struct SectionTableEntry;

        static const std::string undefined_section_entry_name;
        static const std::pair<key_type, mapped_type> undefined_section_entry;
        static const std::string equ_section_entry_name;
        static const std::pair<key_type, mapped_type> equ_section_entry;

        SectionTable();

        mapped_type &at(const key_type &key);
        void insert(const key_type &key);
        void update_section_size(const key_type &key, size_t size);
        void erase(const key_type &key);

        std::stringstream to_school_elf() const;

    private:
        void insert(const std::pair<key_type, mapped_type> &entry);

        std::map<key_type, mapped_type> section_table_;
        size_t next_section_index_ = 2;
    };

} // namespace assembler

#endif
