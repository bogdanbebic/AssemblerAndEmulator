#ifndef _INSTRUCTION_H_
#define _INSTRUCTION_H_

#include "Typedefs.hpp"

namespace emulator
{
	namespace system
	{
		namespace cpu
		{
			namespace instruction
			{
				typedef struct InstructionDescriptor
				{
					byte_t operation_code;
					byte_t operand_size;
				} instruction_descriptor_t;

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
			}
		}
	}
}

#endif
