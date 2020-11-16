#ifndef _PSW_H_
#define _PSW_H_

#include "CpuDefs.hpp"
#include "Typedefs.hpp"

namespace emulator
{
	namespace system
	{
		namespace cpu
		{
			class Psw
			{
			public:
				bool psw_read(PswMasks bit) const;
				void psw_write(PswMasks bit, bool value);
			private:
				void psw_clear(PswMasks bit);
				void psw_set(PswMasks bit);

				word_t psw_ = 0;
			};
		}
	}
}

#endif
