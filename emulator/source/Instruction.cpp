#include "Instruction.hpp"

#include "InstructionsDefs.hpp"

size_t emulator::system::cpu::instruction::number_of_operands(emulator::system::cpu::instruction::instruction_t instr)
{
    if (instr.instruction_descriptor.operation_code <= RET)
        return 0;
    else if (instr.instruction_descriptor.operation_code <= POP)
        return 1;
    else
        return 2;
}
