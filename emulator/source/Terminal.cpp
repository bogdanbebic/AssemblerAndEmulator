#include "Terminal.hpp"

#include <iostream>
#include <utility>

#include "CpuDefs.hpp"

#ifndef _WIN32
#include <unistd.h>
#endif

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
	struct termios raw;
	tcgetattr(STDIN_FILENO, &raw);
	this->old_termios = raw;

	raw.c_lflag &= ~ICANON;

	tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
#endif
}

void emulator::system::Terminal::exit_raw_mode()
{
#ifndef _WIN32
	// Linux
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &this->old_termios);
#endif
}
