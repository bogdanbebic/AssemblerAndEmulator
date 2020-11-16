#include "Cpu.hpp"

#include <stdexcept>
#include <utility>

#include "InstructionsDefs.hpp"

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
	this->general_purpose_registers_[REG_PC] = this->memory_->read_word(this->interrupt_vector_table_pointer_);
	while (this->cpu_running_)
	{
		instruction::instruction_t instr = this->fetch_instruction();
		this->execute_instruction(instr);
		this->handle_interrupt();
	}
}

emulator::system::cpu::instruction::instruction_t emulator::system::cpu::Cpu::fetch_instruction()
{
	using namespace instruction;
	instruction_t instr;
	byte_t instruction_descriptor = this->memory_->read_byte(this->general_purpose_registers_[REG_PC]);
	this->general_purpose_registers_[REG_PC] += sizeof(byte_t);

	instr.instruction_descriptor.operation_code = (instruction_descriptor & OPCODE_MASK) >> OPCODE_OFFSET;
	instr.instruction_descriptor.operand_size	= (instruction_descriptor & OPERAND_SIZE_MASK) >> OPERAND_SIZE_OFFSET;

	for (size_t i = 0; i < number_of_operands(instr) && i < max_operands_in_instruction; i++)
	{
		byte_t operand_descriptor = this->memory_->read_byte(this->general_purpose_registers_[REG_PC]);
		this->general_purpose_registers_[REG_PC] += sizeof(byte_t);

		instr.operands[i].addressing_mode = (operand_descriptor & ADDRESSING_MODE_MASK) >> ADDRESSING_MODE_OFFSET;
		instr.operands[i].register_index = (operand_descriptor & REGISTER_INDEX_MASK) >> REGISTER_INDEX_OFFSET;
		instr.operands[i].low_byte = (operand_descriptor & LOW_BYTE_MASK) >> LOW_BYTE_OFFSET;

		if (instr.operands[i].addressing_mode == REGISTER || instr.operands[i].addressing_mode == REGISTER_INDIRECT)
			continue;

		if (instr.instruction_descriptor.operand_size == OPERAND_SIZE_BYTE)
		{
			instr.operands[i].operand = this->memory_->read_byte(this->general_purpose_registers_[REG_PC]);
			this->general_purpose_registers_[REG_PC] += sizeof(byte_t);
		}
		else
		{
			instr.operands[i].operand = this->memory_->read_word(this->general_purpose_registers_[REG_PC]++);
			this->general_purpose_registers_[REG_PC] += sizeof(word_t);
		}
	}

	return instr;
}

void emulator::system::cpu::Cpu::execute_instruction(instruction::instruction_t instr)
{
	// TODO: implement
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
			this->general_purpose_registers_[REG_PC] = this->memory_->read_word(this->interrupt_vector_table_pointer_ + i * 2);
			break;
		}
	}
}
