#ifndef _TIMER_HPP_
#define _TIMER_HPP_

#include <chrono>
#include <map>
#include <memory>
#include <thread>

#include "Cpu.hpp"
#include "Typedefs.hpp"

namespace emulator
{
    namespace system
    {
        class Timer
        {
        public:
            void set_timer_cfg(word_t timer_cfg);

            explicit Timer(std::shared_ptr<cpu::Cpu> cpu);

            Timer(const Timer &) = delete;
            Timer(Timer &&)      = delete;
            void operator=(const Timer &) = delete;
            void operator=(Timer &&) = delete;

            ~Timer();

        private:
            void timer() const;

            std::shared_ptr<cpu::Cpu> cpu_;

            static std::map<word_t, std::chrono::milliseconds> timeouts_;

            static constexpr word_t timer_cfg_timeout_mask = 0x7;

            word_t timer_cfg_ = 0x0;

            std::chrono::milliseconds timeout_ = timeouts_[timer_cfg_ & timer_cfg_timeout_mask];

            bool running_ = true;
            std::thread timer_thread_{ &Timer::timer, this };
        };
    } // namespace system
} // namespace emulator

#endif
