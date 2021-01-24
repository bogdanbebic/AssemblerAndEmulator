#ifndef _RELOCATION_TABLE_HPP_
#define _RELOCATION_TABLE_HPP_

#include <map>
#include <memory>
#include <string>

namespace assembler
{
    class SymbolTable;

    class RelocationTable
    {
    public:
        explicit RelocationTable(std::shared_ptr<SymbolTable> symbol_table);

        void add_equ_relocation(const std::string &equ_entry_key,
                                const std::string &relocation_entry_key);

    private:
        std::map<std::string, std::string> equ_relocations_;
        std::shared_ptr<SymbolTable> symbol_table_;
    };
} // namespace assembler

#endif
