#ifndef _EMULATOR_H_
#define _EMULATOR_H_

#include <memory>

#include "Cpu.hpp"
#include "Memory.hpp"
#include "Terminal.hpp"
#include "Timer.hpp"

namespace emulator
{
	namespace system
	{
		class Emulator
		{
		public:
			void emulate();
			void load_memory(mem_address_t base, size_t size);
		private:
			std::shared_ptr<cpu::Cpu> cpu_		= std::make_shared<cpu::Cpu>();
			std::shared_ptr<Memory>   memory_	= std::make_shared<Memory>();
			std::shared_ptr<Terminal> terminal_ = std::make_shared<Terminal>(cpu_);
			std::shared_ptr<Timer>	  timer_	= std::make_shared<Timer>(cpu_);

			void map_devices_to_memory();
		};
	}
}

#endif
