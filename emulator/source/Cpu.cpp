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
        this->push_to_stack(this->psw_.get());
        this->general_purpose_registers_[REG_PC] = (this->operand_value(instr, 0) % 8) * 2;
        break;
    case instruction::CALL:
        this->push_to_stack(this->general_purpose_registers_[REG_PC]);
        this->general_purpose_registers_[REG_PC] = this->operand_value(instr, 0);
        break;
    case instruction::JMP:
        this->general_purpose_registers_[REG_PC] = this->operand_value(instr, 0);
        break;
    case instruction::JEQ:
        if (this->psw_.psw_read(PswMasks::PSW_Z_MASK))
            this->general_purpose_registers_[REG_PC] = this->operand_value(instr, 0);
        break;
    case instruction::JNE:
        if (!this->psw_.psw_read(PswMasks::PSW_Z_MASK))
            this->general_purpose_registers_[REG_PC] = this->operand_value(instr, 0);
        break;
    case instruction::JGT:
        if (!this->psw_.psw_read(PswMasks::PSW_Z_MASK) &&
            !this->psw_.psw_read(PswMasks::PSW_N_MASK))
            this->general_purpose_registers_[REG_PC] = this->operand_value(instr, 0);
        break;
    case instruction::PUSH:
        this->push_to_stack(this->operand_value(instr, 0));
        break;
    case instruction::POP:
        this->write_operand(instr, 0, this->pop_from_stack());
        break;
    default:
        throw std::invalid_argument{ "Usage fault: invalid opcode" };
    }
}

void emulator::system::cpu::Cpu::execute_instruction_two_operand(instruction::instruction_t instr)
{
    alu_result_t alu_result;
    auto opcode = instr.instruction_descriptor.operation_code;
    switch (opcode)
    {
    case instruction::XCHG:
    {
        auto op0 = this->operand_value(instr, 0);
        auto op1 = this->operand_value(instr, 1);

        this->write_operand(instr, 1, op0);
        this->write_operand(instr, 0, op1);

        break;
    }

    case instruction::MOV:
    {
        auto op0 = this->operand_value(instr, 0);

        this->psw_.psw_write(PswMasks::PSW_Z_MASK, op0 == 0);
        // this->psw_.psw_write(PswMasks::PSW_N_MASK, <TODO>);

        this->write_operand(instr, 1, op0);

        break;
    }

    // ALU instructions
    case instruction::ADD:
    case instruction::SUB:

        alu_result = this->alu_.execute_operation(
            static_cast<instruction::OperationCodes>(opcode),
            this->operand_value(instr, 0),
            this->operand_value(instr, 1));

        this->psw_.psw_write(PswMasks::PSW_O_MASK, alu_result.o_flag);
        this->psw_.psw_write(PswMasks::PSW_C_MASK, alu_result.c_flag);

        [[fallthrough]];

    case instruction::MUL:
    case instruction::DIV:
    case instruction::NOT:
    case instruction::AND:
    case instruction::OR:
    case instruction::XOR:

        this->psw_.psw_write(PswMasks::PSW_Z_MASK, alu_result.z_flag);
        this->psw_.psw_write(PswMasks::PSW_N_MASK, alu_result.n_flag);

        this->write_operand(instr, 1, alu_result.result);

        break;

    case instruction::SHL:
    case instruction::SHR:

        alu_result = this->alu_.execute_operation(
            static_cast<instruction::OperationCodes>(opcode),
            this->operand_value(instr, 0),
            this->operand_value(instr, 1));

        this->psw_.psw_write(PswMasks::PSW_Z_MASK, alu_result.z_flag);
        this->psw_.psw_write(PswMasks::PSW_C_MASK, alu_result.c_flag);
        this->psw_.psw_write(PswMasks::PSW_N_MASK, alu_result.n_flag);

        this->write_operand(
            instr, opcode == instruction::SHL ? 1 : 0, alu_result.result);

        break;

    case instruction::CMP:
    case instruction::TEST:

        alu_result = this->alu_.execute_operation(
            static_cast<instruction::OperationCodes>(opcode),
            this->operand_value(instr, 0),
            this->operand_value(instr, 1));

        this->psw_.psw_write(PswMasks::PSW_Z_MASK, alu_result.z_flag);
        this->psw_.psw_write(PswMasks::PSW_N_MASK, alu_result.n_flag);

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

void emulator::system::cpu::Cpu::write_operand(instruction::instruction_t instr,
                                               size_t operand_index,
                                               word_t value)
{
    if (instruction::is_operand_in_memory(instr, operand_index))
    {
        auto memory_address = this->operand_memory_address(instr, operand_index);
        if (instr.instruction_descriptor.operand_size == instruction::OPERAND_SIZE_BYTE)
            this->memory_->write_byte(memory_address, static_cast<byte_t>(value & 0xFF));
        else if (instr.instruction_descriptor.operand_size == instruction::OPERAND_SIZE_WORD)
            this->memory_->write_word(memory_address, value);
    }
    else if (instr.operands[operand_index].addressing_mode == instruction::REGISTER)
    {
        auto reg_index = instr.operands[operand_index].register_index;
        if (instr.operands[operand_index].low_byte)
            value &= 0xFF;

        if (reg_index < num_gp_registers)
            this->general_purpose_registers_[reg_index] = value;
        else if (reg_index == instruction::psw_idx)
            this->psw_.set(value);
        else
            throw std::invalid_argument{ "Usage fault: invalid register index" };
    }
    else
    {
        throw std::invalid_argument{ "Usage fault: invalid addressing mode" };
    }
}
