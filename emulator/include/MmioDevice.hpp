#ifndef _MMIO_DEVICE_HPP_
#define _MMIO_DEVICE_HPP_

#include "Typedefs.hpp"

namespace emulator
{
    namespace system
    {
        class MmioDevice
        {
        public:
            virtual word_t get_memory(mem_address_t offset)             = 0;
            virtual void set_memory(mem_address_t offset, word_t value) = 0;

            MmioDevice()                   = default;
            MmioDevice(const MmioDevice &) = default;
            MmioDevice(MmioDevice &&)      = default;
            virtual ~MmioDevice()          = default;
        };
    } // namespace system
} // namespace emulator

#endif
