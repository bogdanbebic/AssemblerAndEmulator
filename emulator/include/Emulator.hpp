#ifndef _EMULATOR_HPP_
#define _EMULATOR_HPP_

#include <memory>
#include <vector>

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
            void load_memory(mem_address_t base,
                             const std::vector<emulator::system::byte_t> &memory_contents);
            void load_memory(const std::vector<emulator::system::byte_t> &memory_contents);

        private:
            std::shared_ptr<Memory> memory_ = std::make_shared<Memory>();
            std::shared_ptr<cpu::Cpu> cpu_ = std::make_shared<cpu::Cpu>(memory_);
            std::shared_ptr<Terminal> terminal_ = std::make_shared<Terminal>(cpu_);
            std::shared_ptr<Timer> timer_       = std::make_shared<Timer>(cpu_);

            enum MmioAdrresses
            {
                MMIO_TERMINAL_START = 0xFF00,
                MMIO_TERMINAL_END   = MMIO_TERMINAL_START + 4,

                MMIO_TIMER_START = 0xFF10,
                MMIO_TIMER_END   = MMIO_TIMER_START + 2,
            };

            void map_devices_to_memory();
        };
    } // namespace system
} // namespace emulator

#endif
