#ifndef _OPERAND_HPP_
#define _OPERAND_HPP_

namespace statement
{
    enum AddressingModes
    {
        IMMEDIATE                = 0x0,
        REGISTER                 = 0x1,
        REGISTER_INDIRECT        = 0x2,
        REGISTER_INDIRECT_OFFSET = 0x3,
        MEMORY_DIRECT            = 0x4,
    };

    typedef struct
    {
        uint8_t addressing_mode;
        uint8_t register_index;
        uint8_t operand[2];
    } operand_t;
} // namespace statement

#endif
