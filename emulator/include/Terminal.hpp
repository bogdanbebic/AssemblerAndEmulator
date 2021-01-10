#ifndef _TERMINAL_HPP_
#define _TERMINAL_HPP_

#include <memory>
#include <thread>

#ifndef _WIN32
#include <termios.h>
#endif

#include "MmioDevice.hpp"

#include "Cpu.hpp"
#include "Typedefs.hpp"

namespace emulator
{
    namespace system
    {
        class Terminal : public MmioDevice
        {
        public:
            word_t get_memory(mem_address_t offset) override;
            void set_memory(mem_address_t offset, word_t value) override;

            explicit Terminal(std::shared_ptr<cpu::Cpu> cpu);

            Terminal(const Terminal &) = delete;
            Terminal(Terminal &&)      = delete;
            void operator=(const Terminal &) = delete;
            void operator=(Terminal &&) = delete;

            ~Terminal();

        private:
            void terminal();

            void enter_raw_mode();
            void exit_raw_mode();

            void set_data_out(word_t data_out);
            word_t data_in() const;

            enum RegsOffset
            {
                DATA_OUT = 0,
                DATA_IN  = 2,
            };

            std::shared_ptr<cpu::Cpu> cpu_;

#ifndef _WIN32
            int old_stdin_flags;
            struct termios old_termios;
#endif

            static constexpr word_t data_out_mask = 0xFF;
            static constexpr word_t data_in_mask  = 0xFF;

            word_t data_out_ = 0;
            word_t data_in_  = 0;

            bool running_ = true;
            std::thread terminal_thread_{ &Terminal::terminal, this };
        };
    } // namespace system
} // namespace emulator

#endif
