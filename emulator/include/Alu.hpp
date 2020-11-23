#ifndef _ALU_HPP_
#define _ALU_HPP_

#include "InstructionsDefs.hpp"
#include "Typedefs.hpp"

namespace emulator
{
    namespace system
    {
        namespace cpu
        {
            typedef struct
            {
                word_t result = 0;
                bool z_flag   = false;
                bool o_flag   = false;
                bool c_flag   = false;
                bool n_flag   = false;
            } alu_result_t;

            class Alu
            {
            public:
                alu_result_t execute_operation(instruction::OperationCodes opcode,
                                               word_t op0,
                                               word_t op1,
                                               byte_t operand_size);
            };
        } // namespace cpu
    }     // namespace system
} // namespace emulator

#endif
