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
                word_t result;
                bool z_flag;
                bool o_flag;
                bool c_flag;
                bool n_flag;
            } alu_result_t;

            class Alu
            {
            public:
                alu_result_t execute_operation(instruction::OperationCodes opcode,
                                               word_t op0,
                                               word_t op1);
                alu_result_t execute_byte_operation(instruction::OperationCodes opcode,
                                                    byte_t op0,
                                                    byte_t op1);
            };
        } // namespace cpu
    }     // namespace system
} // namespace emulator

#endif
