#ifndef _TERMINAL_H_
#define _TERMINAL_H_

#include <thread>

#ifndef _WIN32
#include <termios.h>
#endif

#include "Typedefs.h"

namespace emulator
{
	namespace system
	{
		class Terminal
		{
		public:
			void set_data_out(word_t data_out);
			word_t data_in() const;

			Terminal();

			Terminal(const Terminal&) = delete;
			Terminal(Terminal&&) = delete;
			void operator= (const Terminal&) = delete;
			void operator= (Terminal&&) = delete;
			
			~Terminal();
		private:
			void terminal();

			void enter_raw_mode();
			void exit_raw_mode();

			#ifndef _WIN32
			struct termios old_termios;
			#endif

			static constexpr word_t data_out_mask = 0xFF;
			static constexpr word_t data_in_mask  = 0xFF;
			word_t data_out_ = 0;
			word_t data_in_  = 0;
			
			bool running_ = true;
			std::thread terminal_thread_{ &Terminal::terminal, this };
		};
	}	
}

#endif
