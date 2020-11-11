#ifndef _LINKER_H_
#define _LINKER_H_

#include <string>
#include <vector>
#include <map>
#include "Typedefs.h"

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
}

#endif
