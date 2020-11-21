#include "Alu.hpp"

emulator::system::cpu::alu_result_t emulator::system::cpu::Alu::execute_operation(
    instruction::OperationCodes opcode, word_t op0, word_t op1)
{
    alu_result_t ret;
    switch (opcode)
    {
    case instruction::ADD:
    {
        ret.result = op1 + op0;
        // TODO: Z O C N
    }
    break;
    case instruction::SUB:
    {
        ret.result = op1 - op0;
        // TODO: Z O C N
    }
    break;
    case instruction::MUL:
    {
        ret.result = op1 * op0;
        // TODO: Z N
    }
    break;
    case instruction::DIV:
    {
        ret.result = op1 / op0;
        // TODO: Z N
    }
    break;
    case instruction::CMP:
    {
        // op1 - op0
        // TODO: Z O C N
    }
    break;
    case instruction::NOT:
    {
        ret.result = ~op0;
        // TODO: Z N
    }
    break;
    case instruction::AND:
    {
        ret.result = op1 & op0;
        // TODO: Z N
    }
    break;
    case instruction::OR:
    {
        ret.result = op1 | op0;
        // TODO: Z N
    }
    break;
    case instruction::XOR:
    {
        ret.result = op1 ^ op0;
        // TODO: Z N
    }
    break;
    case instruction::TEST:
    {
        // op1 & op0
        // TODO: Z N
    }
    break;
    case instruction::SHL:
    {
        ret.result = op1 << op0;
        // TODO: Z C N
    }
    break;
    case instruction::SHR:
    {
        ret.result = op0 >> op1;
        // TODO: Z C N
    }
    break;
    default:
        break;
    }

    return ret;
}

emulator::system::cpu::alu_result_t emulator::system::cpu::Alu::execute_byte_operation(
    instruction::OperationCodes opcode, byte_t op0, byte_t op1)
{
    // TODO: implement
    return {};
}
