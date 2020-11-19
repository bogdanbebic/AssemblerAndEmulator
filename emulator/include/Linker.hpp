#ifndef _LINKER_HPP_
#define _LINKER_HPP_

#include <map>
#include <string>
#include <vector>

#include "Typedefs.hpp"

namespace linker
{
    class Linker
    {
    public:
        void link(std::vector<std::string> source_file_paths,
                  std::map<std::string, int> section_address_map);

        std::vector<emulator::system::byte_t> memory_contents() const;

    private:
        std::vector<emulator::system::byte_t> memory_contents_;
    };
} // namespace linker

#endif
