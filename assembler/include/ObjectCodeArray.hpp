#ifndef _OBJECT_CODE_ARRAY_HPP_
#define _OBJECT_CODE_ARRAY_HPP_

#include <sstream>
#include <vector>

#include "DataDefs.hpp"

namespace assembler
{
    class ObjectCodeArray
    {
    public:
        void skip_bytes(size_t number_of_bytes_to_skip);

        void push_back_byte(byte_t byte);
        void push_back_word(word_t word);

        void increment_byte(size_t offset, byte_t increment);
        void increment_word(size_t offset, word_t increment);

        std::stringstream to_school_elf() const;

        size_t size() const;

    private:
        std::vector<byte_t> object_code_;
    };
} // namespace assembler

#endif
