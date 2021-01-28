#ifndef _RELOCATION_TABLE_HPP_
#define _RELOCATION_TABLE_HPP_

#include <map>
#include <memory>
#include <string>
#include <vector>

namespace assembler
{
    class SymbolTable;

    class RelocationTable
    {
    public:
        typedef enum RelocationType
        {
            R_16   = 12,
            R_PC16 = 13,
            R_8    = 14,

            R_SECTION16 = 15,
            R_SECTION8  = 16,
        } relocation_type_t;

        using relocation_offset_t = size_t;

        typedef struct RelocationTableEntry
        {
            std::string symbol;
            relocation_type_t type;
            relocation_offset_t offset = 0;
        } relocation_table_entry_t;

        explicit RelocationTable(std::shared_ptr<SymbolTable> symbol_table);

        void insert(relocation_table_entry_t entry);

        void add_equ_relocation(const std::string &equ_entry_key,
                                const std::string &relocation_entry_key);

        std::stringstream to_school_elf() const;

    private:
        std::vector<relocation_table_entry_t> relocation_table_;

        std::map<std::string, std::string> equ_relocations_;
        std::shared_ptr<SymbolTable> symbol_table_;
    };
} // namespace assembler

#endif
