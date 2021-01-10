#include "Alu.hpp"

#include <stdexcept>

#include "Instruction.hpp"

emulator::system::cpu::alu_result_t emulator::system::cpu::Alu::execute_operation(
    instruction::OperationCodes opcode, word_t op0, word_t op1, byte_t operand_size)
{
    word_t highest_bit_mask = operand_size == instruction::OPERAND_SIZE_BYTE ? 0x0080 : 0x8000;
    alu_result_t ret;
    switch (opcode)
    {
    case instruction::ADD:
        ret.result = op1 + op0;
        ret.c_flag = (op0 & op1 & highest_bit_mask) != 0;
        ret.o_flag = (op1 & op0 & highest_bit_mask && !(ret.result & highest_bit_mask)) ||
                     (!(op1 & highest_bit_mask) && !(op0 & highest_bit_mask) &&
                      ret.result & highest_bit_mask);
        break;

    case instruction::SUB:
        ret.result = op1 - op0;
        for (word_t mask = highest_bit_mask; mask > 0; mask >>= 1)
        {
            if (op1 & mask && (op0 & mask) == 0)
            {
                break;
            }
            if (op0 & mask && (op1 & mask) == 0)
            {
                ret.c_flag = true;
                break;
            }
        }

        ret.o_flag = (op1 & highest_bit_mask && !(op0 & highest_bit_mask) &&
                      !(ret.result & highest_bit_mask)) ||
                     (!(op1 & highest_bit_mask) && op0 & highest_bit_mask &&
                      ret.result & highest_bit_mask);
        break;

    case instruction::MUL:
        ret.result = op1 * op0;
        break;

    case instruction::DIV:
        ret.result = op1 / op0;
        break;

    case instruction::CMP:
        // will not be used
        ret.result = op1 - op0;
        for (word_t mask = highest_bit_mask; mask > 0; mask >>= 1)
        {
            if (op1 & mask && (op0 & mask) == 0)
            {
                break;
            }
            if (op0 & mask && (op1 & mask) == 0)
            {
                ret.c_flag = true;
                break;
            }
        }

        ret.o_flag = (op1 & highest_bit_mask && !(op0 & highest_bit_mask) &&
                      !(ret.result & highest_bit_mask)) ||
                     (!(op1 & highest_bit_mask) && op0 & highest_bit_mask &&
                      ret.result & highest_bit_mask);
        break;

    case instruction::NOT:
        ret.result = ~op0;
        break;

    case instruction::AND:
        ret.result = op1 & op0;
        break;

    case instruction::OR:
        ret.result = op1 | op0;
        break;

    case instruction::XOR:
        ret.result = op1 ^ op0;
        break;

    case instruction::TEST:
        // will not be used
        ret.result = op1 & op0;
        break;

    case instruction::SHL:
        ret.result = op1 << op0;
        if (op0 > 0)
            ret.c_flag = ((op1 << (op0 - 1)) & highest_bit_mask) != 0;
        break;

    case instruction::SHR:
        ret.result = op0 >> op1;
        if (op0 > 0)
            ret.c_flag = ((op0 >> (op1 - 1)) & 1) != 0;
        break;

    default:
        throw std::invalid_argument{ "Usage fault: invalid opcode for ALU" };
    }

    ret.z_flag = ret.result == 0;

    if (operand_size == instruction::OPERAND_SIZE_BYTE)
        ret.n_flag = static_cast<signed_byte_t>(op0) < 0;
    else
        ret.n_flag = static_cast<signed_word_t>(op0) < 0;

    return ret;
}
