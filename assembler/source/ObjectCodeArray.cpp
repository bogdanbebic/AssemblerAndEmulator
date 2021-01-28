#include "ObjectCodeArray.hpp"

void assembler::ObjectCodeArray::skip_bytes(size_t number_of_bytes_to_skip)
{
    for (size_t i = 0; i < number_of_bytes_to_skip; i++)
    {
        this->push_back_byte(0);
    }
}

void assembler::ObjectCodeArray::push_back_byte(byte_t byte)
{
    this->object_code_.push_back(byte);
}

void assembler::ObjectCodeArray::push_back_word(word_t word)
{
    const auto lower_byte = static_cast<byte_t>(word & 0xff);
    const auto upper_byte = static_cast<byte_t>((word & 0xff00) >> 8);

    this->object_code_.push_back(lower_byte);
    this->object_code_.push_back(upper_byte);
}

void assembler::ObjectCodeArray::increment_byte(size_t offset, byte_t increment)
{
    this->object_code_.at(offset) += increment;
}

void assembler::ObjectCodeArray::increment_word(size_t offset, word_t increment)
{
    const word_t result = increment + this->object_code_.at(offset) +
                          (static_cast<word_t>(this->object_code_.at(offset + 1)) << 8);

    const auto lower_byte = static_cast<byte_t>(result & 0xff);
    const auto upper_byte = static_cast<byte_t>((result & 0xff00) >> 8);

    this->object_code_.at(offset)     = lower_byte;
    this->object_code_.at(offset + 1) = upper_byte;
}

std::stringstream assembler::ObjectCodeArray::to_school_elf() const
{
    std::stringstream school_elf_stream;
    school_elf_stream << "##########\n";
    school_elf_stream << "# School ELF object code:\n";

    for (byte_t byte : this->object_code_)
    {
        school_elf_stream << byte;
    }

    school_elf_stream << "\n##########\n";
    return school_elf_stream;
}

size_t assembler::ObjectCodeArray::size() const
{
    return this->object_code_.size();
}
