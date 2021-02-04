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

    this->memory_[base_address]     = static_cast<byte_t>(data & 0x00FF);
    this->memory_[base_address + 1] = static_cast<byte_t>((data & 0xFF00) >> 8);
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

    return this->memory_[base_address] +
           (static_cast<word_t>(this->memory_[base_address + 1]) << 8);
}

void emulator::system::Memory::add_mmio_device(std::shared_ptr<MmioDevice> device,
                                               mem_address_t start_address,
                                               mem_address_t end_address)
{
    this->mmio_devices.push_back({ device, start_address, end_address });
}

void emulator::system::Memory::write_mmio_byte(mem_address_t address, byte_t data)
{
    mem_address_t aligned_address = address & ~1;
    word_t data_value             = this->read_mmio_word(aligned_address);

    if (aligned_address == address)
    {
        data_value &= 0x00FF;
        data_value &= data << 8;
    }
    else
    {
        data_value &= 0xFF00;
        data_value &= data;
    }

    this->write_mmio_word(aligned_address, data_value);
}

emulator::system::byte_t emulator::system::Memory::read_mmio_byte(mem_address_t address)
{
    mem_address_t aligned_address = address & ~1;
    word_t data_value             = this->read_mmio_word(aligned_address);

    if (aligned_address == address)
    {
        data_value &= 0x00FF;
    }
    else
    {
        data_value &= 0xFF00;
        data_value >>= 8;
    }

    return static_cast<byte_t>(data_value);
}

void emulator::system::Memory::write_mmio_word(mem_address_t address, word_t data)
{
    for (auto &mmio_device : this->mmio_devices)
        if (address >= mmio_device.start_address && address < mmio_device.end_address)
            mmio_device.device->set_memory(address - mmio_device.start_address, data);
}

emulator::system::word_t emulator::system::Memory::read_mmio_word(mem_address_t address)
{
    for (auto &mmio_device : this->mmio_devices)
        if (address >= mmio_device.start_address && address < mmio_device.end_address)
            return mmio_device.device->get_memory(address - mmio_device.start_address);

    // no device mapped
    return 0;
}
