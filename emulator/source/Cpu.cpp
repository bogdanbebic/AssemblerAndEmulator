#include "Cpu.hpp"

#include <stdexcept>
#include <utility>

#include "InstructionsDefs.hpp"
#include "StackOverflow.hpp"
#include "StackUnderflow.hpp"

emulator::system::cpu::Cpu::Cpu(std::shared_ptr<Memory> memory)
    : memory_(std::move(memory))
{
    // empty body
}

void emulator::system::cpu::Cpu::interrupt(const size_t ivt_entry)
{
    if (ivt_entry >= ivt_num_entries)
        throw std::invalid_argument{ "Usage fault: invalid ivt_entry" };
    this->interrupt_pending_[ivt_entry] = true;
}

void emulator::system::cpu::Cpu::work()
{
    this->cpu_running_ = true;
    this->general_purpose_registers_[REG_PC] =
        this->memory_->read_word(this->interrupt_vector_table_pointer_);
    while (this->cpu_running_)
    {
        instruction::instruction_t instr = this->fetch_instruction();
        this->execute_instruction(instr);
        this->handle_interrupt();
    }
}

void emulator::system::cpu::Cpu::push_to_stack(word_t word)
{
    if (this->general_purpose_registers_[REG_SP] == sizeof(word_t))
        throw exceptions::StackOverflow{};

    this->general_purpose_registers_[REG_SP] -= sizeof(word_t);
    this->memory_->write_word(this->general_purpose_registers_[REG_SP], word);
}

emulator::system::word_t emulator::system::cpu::Cpu::pop_from_stack()
{
    if (this->general_purpose_registers_[REG_SP] == 0)
        throw exceptions::StackUnderflow{};

    auto ret = this->memory_->read_word(this->general_purpose_registers_[REG_SP]);
    this->general_purpose_registers_[REG_SP] += sizeof(word_t);
    return ret;
}

emulator::system::cpu::instruction::instruction_t emulator::system::cpu::Cpu::fetch_instruction()
{
    using namespace instruction;
    instruction_t instr;
    byte_t instruction_descriptor =
        this->memory_->read_byte(this->general_purpose_registers_[REG_PC]);
    this->general_purpose_registers_[REG_PC] += sizeof(byte_t);

    instr.instruction_descriptor.operation_code =
        (instruction_descriptor & OPCODE_MASK) >> OPCODE_OFFSET;
    instr.instruction_descriptor.operand_size =
        (instruction_descriptor & OPERAND_SIZE_MASK) >> OPERAND_SIZE_OFFSET;

    for (size_t i = 0; i < number_of_operands(instr) && i < max_operands_in_instruction; i++)
    {
        byte_t operand_descriptor =
            this->memory_->read_byte(this->general_purpose_registers_[REG_PC]);
        this->general_purpose_registers_[REG_PC] += sizeof(byte_t);

        instr.operands[i].addressing_mode =
            (operand_descriptor & ADDRESSING_MODE_MASK) >> ADDRESSING_MODE_OFFSET;
        instr.operands[i].register_index =
            (operand_descriptor & REGISTER_INDEX_MASK) >> REGISTER_INDEX_OFFSET;
        instr.operands[i].low_byte = (operand_descriptor & LOW_BYTE_MASK) >> LOW_BYTE_OFFSET;

        if (instr.operands[i].addressing_mode == REGISTER ||
            instr.operands[i].addressing_mode == REGISTER_INDIRECT)
            continue;

        if (instr.instruction_descriptor.operand_size == OPERAND_SIZE_BYTE)
        {
            instr.operands[i].operand =
                this->memory_->read_byte(this->general_purpose_registers_[REG_PC]);
            this->general_purpose_registers_[REG_PC] += sizeof(byte_t);
        }
        else
        {
            instr.operands[i].operand =
                this->memory_->read_word(this->general_purpose_registers_[REG_PC]++);
            this->general_purpose_registers_[REG_PC] += sizeof(word_t);
        }
    }

    return instr;
}

void emulator::system::cpu::Cpu::execute_instruction(instruction::instruction_t instr)
{
    switch (instruction::number_of_operands(instr))
    {
    case 0:
        this->execute_instruction_zero_operand(instr);
        break;
    case 1:
        this->execute_instruction_one_operand(instr);
        break;
    case 2:
        this->execute_instruction_two_operand(instr);
        break;
    default:;
    }
}

void emulator::system::cpu::Cpu::handle_interrupt()
{
    for (size_t i = 0; i < ivt_num_entries; i++)
    {
        if (this->interrupt_pending_[i])
        {
            this->interrupt_pending_[i] = false;
            // TODO: push pc
            // TODO: push psw
            this->general_purpose_registers_[REG_PC] = this->memory_->read_word(
                this->interrupt_vector_table_pointer_ + i * 2);
            break;
        }
    }
}

void emulator::system::cpu::Cpu::execute_instruction_zero_operand(instruction::instruction_t instr)
{
    switch (instr.instruction_descriptor.operation_code)
    {
    case instruction::HALT:
        this->cpu_running_ = false;
        break;
    case instruction::IRET:
        this->psw_.set(this->pop_from_stack());
        this->general_purpose_registers_[REG_PC] = this->pop_from_stack();
        break;
    case instruction::RET:
        this->general_purpose_registers_[REG_PC] = this->pop_from_stack();
        break;
    default:
        throw std::invalid_argument{ "Usage fault: invalid opcode" };
    }
}

void emulator::system::cpu::Cpu::execute_instruction_one_operand(instruction::instruction_t instr)
{
    switch (instr.instruction_descriptor.operation_code)
    {
    case instruction::INT:
        // TODO: implement
        break;
    case instruction::CALL:
        // TODO: implement
        break;
    case instruction::JMP:
        // TODO: implement
        break;
    case instruction::JEQ:
        // TODO: implement
        break;
    case instruction::JNE:
        // TODO: implement
        break;
    case instruction::JGT:
        // TODO: implement
        break;
    case instruction::PUSH:
        // TODO: implement
        break;
    case instruction::POP:
        // TODO: implement
        break;
    default:
        throw std::invalid_argument{ "Usage fault: invalid opcode" };
    }
}

void emulator::system::cpu::Cpu::execute_instruction_two_operand(instruction::instruction_t instr)
{
    switch (instr.instruction_descriptor.operation_code)
    {
    case instruction::XCHG:
        // TODO: implement
        break;
    case instruction::MOV:
        // TODO: implement
        break;
    case instruction::ADD:
        // TODO: implement
        break;
    case instruction::SUB:
        // TODO: implement
        break;
    case instruction::MUL:
        // TODO: implement
        break;
    case instruction::DIV:
        // TODO: implement
        break;
    case instruction::CMP:
        // TODO: implement
        break;
    case instruction::NOT:
        // TODO: implement
        break;
    case instruction::AND:
        // TODO: implement
        break;
    case instruction::OR:
        // TODO: implement
        break;
    case instruction::XOR:
        // TODO: implement
        break;
    case instruction::TEST:
        // TODO: implement
        break;
    case instruction::SHL:
        // TODO: implement
        break;
    case instruction::SHR:
        // TODO: implement
        break;
    default:
        throw std::invalid_argument{ "Usage fault: invalid opcode" };
    }
}

emulator::system::mem_address_t
emulator::system::cpu::Cpu::operand_memory_address(instruction::instruction_t instr,
                                                   size_t operand_index)
{
    word_t ret;
    switch (instr.operands[operand_index].addressing_mode)
    {
    case instruction::REGISTER_INDIRECT:
        ret = this->general_purpose_registers_[instr.operands[operand_index].register_index];
        break;
    case instruction::REGISTER_INDIRECT_OFFSET:
    {
        auto reg_value =
            this->general_purpose_registers_[instr.operands[operand_index].register_index];
        auto offset = instr.operands[operand_index].operand;

        ret = reg_value + offset;
    }
    break;
    case instruction::MEMORY_DIRECT:
        ret = instr.operands[operand_index].operand;
        break;
    default:
        throw std::invalid_argument{ "Usage fault: invalid addressing mode" };
    }

    return ret;
}

emulator::system::word_t emulator::system::cpu::Cpu::operand_value(instruction::instruction_t instr,
                                                                   size_t operand_index)
{
    word_t ret;
    if (instruction::is_operand_in_memory(instr, operand_index))
    {
        ret = this->memory_->read_word(this->operand_memory_address(instr, operand_index));
    }
    else
    {
        switch (instr.operands[operand_index].addressing_mode)
        {
        case instruction::IMMEDIATE:
            ret = instr.operands[operand_index].operand;
            break;
        case instruction::REGISTER:
            ret = this->general_purpose_registers_[instr.operands[operand_index].register_index];
            break;
        default:
            throw std::invalid_argument{ "Usage fault: invalid addressing mode" };
        }
    }

    if ((instr.operands[operand_index].addressing_mode == instruction::REGISTER &&
         instr.operands[operand_index].low_byte) ||
        instr.instruction_descriptor.operand_size == instruction::OPERAND_SIZE_BYTE)
        ret &= 0xFF;
    return ret;
}
