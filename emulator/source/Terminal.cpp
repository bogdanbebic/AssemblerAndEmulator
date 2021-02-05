#include "Terminal.hpp"

#include <iostream>
#include <utility>

#include "CpuDefs.hpp"
#include "MemoryAccessViolation.hpp"

#ifndef _WIN32
#include <fcntl.h>
#include <unistd.h>
#endif

emulator::system::word_t emulator::system::Terminal::get_memory(mem_address_t offset)
{
    switch (offset)
    {
    case DATA_IN:
        return this->data_in();
    default:
        throw exceptions::MemoryAccessViolation{ "Terminal (get_memory): Invalid memory offset" };
    }
}

void emulator::system::Terminal::set_memory(mem_address_t offset, word_t value)
{
    switch (offset)
    {
    case DATA_OUT:
        this->set_data_out(value);
        break;
    default:
        throw exceptions::MemoryAccessViolation{ "Terminal (set_memory): Invalid memory offset" };
    }
}

void emulator::system::Terminal::set_data_out(const word_t data_out)
{
    this->data_out_ = data_out & data_out_mask;

    // write data_out to terminal
    std::cout << static_cast<char>(this->data_out_);
}

emulator::system::word_t emulator::system::Terminal::data_in() const
{
    return this->data_in_;
}

emulator::system::Terminal::Terminal(std::shared_ptr<cpu::Cpu> cpu)
    : cpu_(std::move(cpu))
{
    this->enter_raw_mode();
}

emulator::system::Terminal::~Terminal()
{
    this->running_ = false;
    this->terminal_thread_.join();
    this->exit_raw_mode();
}

void emulator::system::Terminal::terminal()
{
    while (this->running_)
    {
        char ch;

        // read one char
#ifdef _WIN32
        std::cin >> ch;
#else
        // Linux
        if (read(STDIN_FILENO, &ch, 1) != 1)
        {
            continue;
        }
#endif

        this->data_in_ = ch & data_in_mask;

        this->cpu_->interrupt(cpu::IVT_TERMINAL);
    }
}

void emulator::system::Terminal::enter_raw_mode()
{
#ifndef _WIN32
    // Linux

    int flags = fcntl(STDIN_FILENO, F_GETFL, 0);

    this->old_stdin_flags = flags;
    fcntl(STDIN_FILENO, F_SETFL, flags | O_NONBLOCK);

    struct termios raw;
    tcgetattr(STDIN_FILENO, &raw);
    this->old_termios = raw;

    raw.c_lflag &= ~ICANON;
    raw.c_cc[VMIN]  = 0;
    raw.c_cc[VTIME] = 0;

    tcsetattr(STDIN_FILENO, TCSANOW, &raw);
#endif
}

void emulator::system::Terminal::exit_raw_mode()
{
#ifndef _WIN32
    // Linux
    tcsetattr(STDIN_FILENO, TCSANOW, &this->old_termios);
    fcntl(STDIN_FILENO, F_SETFL, this->old_stdin_flags);
#endif
}
