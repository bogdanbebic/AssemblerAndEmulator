#include "Emulator.hpp"

void emulator::system::Emulator::emulate()
{
    this->map_devices_to_memory();
    this->cpu_->work();
}

void emulator::system::Emulator::load_memory(mem_address_t base,
                                             const std::vector<emulator::system::byte_t> &memory_contents)
{
    for (auto byte : memory_contents)
        this->memory_->write_byte(base++, byte);
}

void emulator::system::Emulator::load_memory(const std::vector<emulator::system::byte_t> &memory_contents)
{
    this->load_memory(0, memory_contents);
}

void emulator::system::Emulator::map_devices_to_memory()
{
    this->memory_->add_mmio_device(this->terminal_, MMIO_TERMINAL_START, MMIO_TERMINAL_END);
    this->memory_->add_mmio_device(this->timer_, MMIO_TIMER_START, MMIO_TIMER_END);
}
