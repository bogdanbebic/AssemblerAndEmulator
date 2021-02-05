#include "Timer.hpp"

#include <utility>

#include "CpuDefs.hpp"
#include "MemoryAccessViolation.hpp"

std::map<emulator::system::word_t, std::chrono::milliseconds> emulator::system::Timer::timeouts_ = {
    { 0x0, std::chrono::milliseconds{ 500 } },
    { 0x1, std::chrono::milliseconds{ 1000 } },
    { 0x2, std::chrono::milliseconds{ 1500 } },
    { 0x3, std::chrono::milliseconds{ 2000 } },
    { 0x4, std::chrono::milliseconds{ 5000 } },
    { 0x5, std::chrono::seconds{ 10 } },
    { 0x6, std::chrono::seconds{ 30 } },
    { 0x7, std::chrono::seconds{ 60 } },
};

emulator::system::word_t emulator::system::Timer::get_memory(mem_address_t offset)
{
    switch (offset)
    {
    default:
        throw exceptions::MemoryAccessViolation{ "Timer (get_memory): Invalid memory offset" };
    }
}

void emulator::system::Timer::set_memory(mem_address_t offset, word_t value)
{
    switch (offset)
    {
    case TIMER_CFG:
        this->set_timer_cfg(value);
        break;
    default:
        throw exceptions::MemoryAccessViolation{ "Timer (set_memory): Invalid memory offset" };
    }
}

void emulator::system::Timer::set_timer_cfg(const word_t timer_cfg)
{
    this->timer_cfg_ = timer_cfg;

    this->timeout_ = timeouts_[this->timer_cfg_ & timer_cfg_timeout_mask];
}

emulator::system::Timer::Timer(std::shared_ptr<cpu::Cpu> cpu)
    : cpu_(std::move(cpu))
{
    // empty body
}

emulator::system::Timer::~Timer()
{
    this->running_ = false;
    this->timer_thread_.join();
}

void emulator::system::Timer::timer() const
{
    while (this->running_)
    {
        this->cpu_->interrupt(cpu::IVT_TIMER);

        std::this_thread::sleep_for(this->timeout_);
    }
}
