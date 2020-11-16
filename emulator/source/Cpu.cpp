#include "Cpu.hpp"

#include <stdexcept>
#include <utility>

emulator::system::cpu::Cpu::Cpu(std::shared_ptr<Memory> memory)
	: memory_(std::move(memory))
{
	// empty body
}

emulator::system::cpu::instruction::instruction_t emulator::system::cpu::Cpu::fetch_instruction() const
{
	// TODO: implement
	return {};
}

void emulator::system::cpu::Cpu::execute_instruction(instruction::instruction_t instr)
{
	// TODO: implement
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
