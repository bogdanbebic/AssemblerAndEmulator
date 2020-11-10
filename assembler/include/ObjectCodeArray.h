#ifndef OBJECT_CODE_ARRAY_H_GUARD
#define OBJECT_CODE_ARRAY_H_GUARD

#include <vector>
#include <sstream>

#include "DataDefs.h"

namespace assembler
{
	class ObjectCodeArray
	{
	public:
		void skip_bytes(size_t number_of_bytes_to_skip);
		
		void push_back_byte(byte_t byte);
		void push_back_word(word_t word);

		std::stringstream to_school_elf() const;
	private:
		std::vector<byte_t> object_code_;
	};
}

#endif
