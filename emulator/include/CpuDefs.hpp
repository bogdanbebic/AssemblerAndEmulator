#ifndef _CPU_DEFS_H_
#define _CPU_DEFS_H_

#include <cstdlib>

#include "Typedefs.hpp"

namespace emulator
{
	namespace system
	{
		namespace cpu
		{
			constexpr size_t size_memory_mapped_registers = 256;

			constexpr size_t num_gp_registers = 8;
			enum GpRegisters
			{
				REG_PC = 6,
				REG_SP = 7,
			};

			constexpr size_t ivt_num_entries = 8;
			enum IvtEntries
			{
				IVT_PROC_START = 0,
				IVT_INVALID_OP = 1,
				IVT_TIMER = 2,
				IVT_TERMINAL = 3,
				/* others free for use */
			};

			using ivt_entry_t = word_t;
			
			enum class PswMasks
			{
				PSW_Z_MASK	= 1 << 0,
				PSW_O_MASK	= 1 << 1,
				PSW_C_MASK	= 1 << 2,
				PSW_N_MASK	= 1 << 3,
				/* free space */
				PSW_TR_MASK = 1 << 13,
				PSW_TL_MASK = 1 << 14,
				PSW_I_MASK	= 1 << 15,
			};
		}
	}
}

#endif
