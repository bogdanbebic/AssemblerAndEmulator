#include "Memory.hpp"

#include "MemoryAccessViolation.hpp"

void emulator::system::Memory::write_byte(const mem_address_t base_address, const byte_t data)
{
    if (base_address >= MMIO_START_ADDRESS && base_address < MMIO_END_ADDRESS)
    {
        this->write_mmio_byte(base_address, data);
        return;
    }

    this->memory_[base_address] = data;
}

emulator::system::byte_t emulator::system::Memory::read_byte(const mem_address_t base_address)
{
    if (base_address >= MMIO_START_ADDRESS && base_address < MMIO_END_ADDRESS)
    {
        return this->read_mmio_byte(base_address);
    }

    return this->memory_[base_address];
}

void emulator::system::Memory::write_word(const mem_address_t base_address, const word_t data)
{
    if (base_address == MEMORY_SIZE - 1)
    {
        throw exceptions::MemoryAccessViolation{};
    }

    if (base_address >= MMIO_START_ADDRESS && base_address < MMIO_END_ADDRESS)
    {
        this->write_mmio_word(base_address, data);
        return;
    }

    const auto memory = reinterpret_cast<word_t *>(this->memory_);
    memory[base_address / sizeof(byte_t) * sizeof(word_t)] = data;
}

emulator::system::word_t emulator::system::Memory::read_word(const mem_address_t base_address)
{
    if (base_address == MEMORY_SIZE - 1)
    {
        throw exceptions::MemoryAccessViolation{};
    }

    if (base_address >= MMIO_START_ADDRESS && base_address < MMIO_END_ADDRESS)
    {
        return this->read_mmio_word(base_address);
    }

    const auto memory = reinterpret_cast<word_t *>(this->memory_);
    return memory[base_address / sizeof(byte_t) * sizeof(word_t)];
}

void emulator::system::Memory::write_mmio_byte(mem_address_t address, byte_t data)
{
    // TODO: implementation
}

emulator::system::byte_t emulator::system::Memory::read_mmio_byte(mem_address_t address)
{
    // TODO: implementation
    return 0;
}

void emulator::system::Memory::write_mmio_word(mem_address_t address, word_t data)
{
    // TODO: implementation
}

emulator::system::word_t emulator::system::Memory::read_mmio_word(mem_address_t address)
{
    // TODO: implementation
    return 0;
}
