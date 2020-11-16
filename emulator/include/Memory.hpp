#ifndef _MEMORY_H_
#define _MEMORY_H_

#include "Typedefs.hpp"

namespace emulator
{
	namespace system
	{
		class Memory
		{
		public:
			void write_byte(mem_address_t base_address, byte_t data);
			byte_t read_byte(mem_address_t base_address);

			void write_word(mem_address_t base_address, word_t data);
			word_t read_word(mem_address_t base_address);
			
			enum { MEMORY_SIZE = mem_address_max + 1 };
		private:
			byte_t memory_[MEMORY_SIZE] = { 0, };

			void write_mem_mapped_register_byte(mem_address_t register_address, byte_t data);
			byte_t read_mem_mapped_register_byte(mem_address_t register_address);
			
			void write_mem_mapped_register_word(mem_address_t register_address, word_t data);
			word_t read_mem_mapped_register_word(mem_address_t register_address);
			
			enum
			{
				MEM_MAP_REGISTERS_START_ADDRESS = 0xFF00,
				MEM_MAP_TERM_DATA_OUT = 0xFF00,
				MEM_MAP_TERM_DATA_IN = 0xFF02,
				MEM_MAP_TIMER_CFG = 0xFF10,
			};
		};
	}
}

#endif
