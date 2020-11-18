#ifndef _CPU_H_
#define _CPU_H_

#include <atomic>
#include <memory>

#include "CpuDefs.hpp"
#include "Instruction.hpp"
#include "Memory.hpp"
#include "Psw.hpp"
#include "Typedefs.hpp"

namespace emulator
{
    namespace system
    {
        namespace cpu
        {
            class Cpu
            {
            public:
                Cpu(std::shared_ptr<Memory> memory);

                Cpu(const Cpu &) = delete;
                Cpu(Cpu &&)      = delete;
                void operator=(const Cpu &) = delete;
                void operator=(Cpu &&) = delete;

                void interrupt(size_t ivt_entry);
                void work();

            private:
                instruction::instruction_t fetch_instruction();
                void execute_instruction(instruction::instruction_t instr);
                void handle_interrupt();

                void execute_instruction_zero_operand(instruction::instruction_t instr);
                void execute_instruction_one_operand(instruction::instruction_t instr);
                void execute_instruction_two_operand(instruction::instruction_t instr);

                std::shared_ptr<Memory> memory_;
                bool cpu_running_ = false;

                byte_t memory_mapped_registers_[size_memory_mapped_registers] = {
                    0,
                };
                word_t general_purpose_registers_[num_gp_registers] = {
                    0,
                };

                const mem_address_t interrupt_vector_table_pointer_ = 0;
                std::atomic_bool interrupt_pending_[ivt_num_entries];

                Psw psw_;
            };
        } // namespace cpu
    }     // namespace system
} // namespace emulator

#endif
