#include "Emulator.hpp"

void emulator::system::Emulator::emulate()
{
	this->map_devices_to_memory();
	this->cpu_->work();
}

void emulator::system::Emulator::load_memory(mem_address_t base, size_t size)
{
	// TODO: implement
}

void emulator::system::Emulator::map_devices_to_memory()
{
	// TODO: implement
}
