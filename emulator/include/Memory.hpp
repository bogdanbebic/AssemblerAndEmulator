#ifndef _MEMORY_HPP_
#define _MEMORY_HPP_

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

            enum
            {
                MEMORY_SIZE     = mem_address_max + 1,
                MMIO_SPACE_SIZE = 256,
            };

        private:
            byte_t memory_[MEMORY_SIZE] = {
                0,
            };

            void write_mmio_byte(mem_address_t address, byte_t data);
            byte_t read_mmio_byte(mem_address_t address);

            void write_mmio_word(mem_address_t address, word_t data);
            word_t read_mmio_word(mem_address_t address);

            enum MmioAdrresses
            {
                MMIO_START_ADDRESS = 0xFF00,

                MMIO_TERMINAL_START = 0xFF00,
                MMIO_TERMINAL_END   = MMIO_TERMINAL_START + 4,

                MMIO_TIMER_START = 0xFF10,
                MMIO_TIMER_END   = MMIO_TIMER_START + 2,

                MMIO_END_ADDRESS = MMIO_START_ADDRESS + MMIO_SPACE_SIZE,
            };
        };
    } // namespace system
} // namespace emulator

#endif
