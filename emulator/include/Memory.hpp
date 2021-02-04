#ifndef _MEMORY_HPP_
#define _MEMORY_HPP_

#include <memory>
#include <vector>

#include "MmioDevice.hpp"
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

            void add_mmio_device(std::shared_ptr<MmioDevice> device,
                                 mem_address_t start_address,
                                 mem_address_t end_address);

            enum
            {
                MEMORY_SIZE = mem_address_max + 1,

                MMIO_SPACE_SIZE    = 0x100,
                MMIO_START_ADDRESS = 0xFF00,
                MMIO_END_ADDRESS   = MMIO_START_ADDRESS + MMIO_SPACE_SIZE,

                STACK_START_ADDRESS = MMIO_START_ADDRESS,
            };

        private:
            byte_t memory_[MEMORY_SIZE] = {
                0,
            };

            typedef struct MmioMapping
            {
                std::shared_ptr<MmioDevice> device;
                mem_address_t start_address;
                mem_address_t end_address;
            } mmio_mapping_t;

            void write_mmio_byte(mem_address_t address, byte_t data);
            byte_t read_mmio_byte(mem_address_t address);

            void write_mmio_word(mem_address_t address, word_t data);
            word_t read_mmio_word(mem_address_t address);

            std::vector<mmio_mapping_t> mmio_devices;
        };
    } // namespace system
} // namespace emulator

#endif
