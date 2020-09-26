#ifndef _TIMER_H_
#define _TIMER_H_

#include <chrono>
#include <map>
#include <thread>

#include "Typedefs.h"

namespace emulator
{
	namespace system
	{
		class Timer
		{
		public:
			void set_timer_cfg(word_t timer_cfg);

			Timer() = default;

			Timer(const Timer&) = delete;
			Timer(Timer&&) = delete;
			void operator= (const Timer&) = delete;
			void operator= (Timer&&) = delete;
			
			~Timer();
		private:
			void timer() const;

			static std::map<word_t, std::chrono::milliseconds> timeouts_;

			static constexpr word_t timer_cfg_timeout_mask = 0x7;
			word_t timer_cfg_ = 0x0;
			std::chrono::milliseconds timeout_ = timeouts_[timer_cfg_ & timer_cfg_timeout_mask];

			bool running_ = true;
			std::thread timer_thread_{ &Timer::timer, this };
		};
	}
}

#endif
