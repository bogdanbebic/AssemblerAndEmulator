#ifndef _CPU_H_
#define _CPU_H_

#include "CpuDefs.h"
#include "Typedefs.h"
#include "Psw.h"

namespace emulator
{
	namespace system
	{
		namespace cpu
		{
			class Cpu
			{
			public:
				void interrupt(size_t ivt_entry);
			private:
				byte_t memory_mapped_registers_[size_memory_mapped_registers] = { 0, };
				word_t general_purpose_registers_[num_gp_registers] = { 0, };
			
				const mem_address_t interrupt_vector_table_pointer_ = 0;

				Psw psw_;
			};
		}
	}
}

#endif
