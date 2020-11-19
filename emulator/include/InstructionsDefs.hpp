#ifndef _INSTRUCTION_DEFS_HPP_
#define _INSTRUCTION_DEFS_HPP_

namespace emulator
{
    namespace system
    {
        namespace cpu
        {
            namespace instruction
            {
                enum OperationCodes
                {
                    HALT = 0x0,
                    IRET = 0x1,
                    RET  = 0x2,
                    INT  = 0x3,
                    CALL = 0x4,
                    JMP  = 0x5,
                    JEQ  = 0x6,
                    JNE  = 0x7,
                    JGT  = 0x8,
                    PUSH = 0x9,
                    POP  = 0xA,
                    XCHG = 0xB,
                    MOV  = 0xC,
                    ADD  = 0xD,
                    SUB  = 0xE,
                    MUL  = 0xF,
                    DIV  = 0x10,
                    CMP  = 0x11,
                    NOT  = 0x12,
                    AND  = 0x13,
                    OR   = 0x14,
                    XOR  = 0x15,
                    TEST = 0x16,
                    SHL  = 0x17,
                    SHR  = 0x18,
                };

                enum AddressingModes
                {
                    IMMEDIATE                = 0x0,
                    REGISTER                 = 0x1,
                    REGISTER_INDIRECT        = 0x2,
                    REGISTER_INDIRECT_OFFSET = 0x3,
                    MEMORY_DIRECT            = 0x4,
                };

                constexpr size_t psw_idx = 0xF;
            } // namespace instruction
        }     // namespace cpu
    }         // namespace system
} // namespace emulator

#endif
