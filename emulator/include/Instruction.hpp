#ifndef _INSTRUCTION_HPP_
#define _INSTRUCTION_HPP_

#include <cstdlib>

#include "Typedefs.hpp"

namespace emulator
{
    namespace system
    {
        namespace cpu
        {
            namespace instruction
            {
                enum InstructionDescriptorConstants
                {
                    OPCODE_MASK         = 0xF8,
                    OPCODE_OFFSET       = 3,
                    OPERAND_SIZE_MASK   = 1 << 2,
                    OPERAND_SIZE_OFFSET = 2,
                    OPERAND_SIZE_BYTE   = 0,
                    OPERAND_SIZE_WORD   = 1,
                };

                typedef struct InstructionDescriptor
                {
                    byte_t operation_code;
                    byte_t operand_size;
                } instruction_descriptor_t;

                enum OperandDescriptorConstants
                {
                    ADDRESSING_MODE_MASK   = 0xE0,
                    ADDRESSING_MODE_OFFSET = 5,
                    REGISTER_INDEX_MASK    = 0x1E,
                    REGISTER_INDEX_OFFSET  = 1,
                    LOW_BYTE_MASK          = 1,
                    LOW_BYTE_OFFSET        = 0,
                };

                typedef struct OperandDescriptor
                {
                    byte_t addressing_mode;
                    byte_t register_index;
                    bool low_byte;
                    word_t operand;
                } operand_descriptor_t;

                constexpr size_t max_operands_in_instruction = 2;

                typedef struct Instruction
                {
                    instruction_descriptor_t instruction_descriptor;
                    operand_descriptor_t operands[max_operands_in_instruction];
                } instruction_t;

                size_t number_of_operands(instruction_t instr);
                bool is_operand_in_memory(instruction_t instr, size_t operand_index);
            } // namespace instruction
        }     // namespace cpu
    }         // namespace system
} // namespace emulator

#endif
