#ifndef _TYPEDEFS_HPP_
#define _TYPEDEFS_HPP_

#include <cstdint>

namespace emulator
{
    namespace system
    {
        using mem_address_t = uint16_t;

        using byte_t = uint8_t;
        using word_t = uint16_t;

        using signed_byte_t = int8_t;
        using signed_word_t = int16_t;

        constexpr mem_address_t mem_address_max = UINT16_MAX;

        constexpr byte_t byte_max = UINT8_MAX;
        constexpr word_t word_max = UINT16_MAX;
    } // namespace system
} // namespace emulator

#endif
