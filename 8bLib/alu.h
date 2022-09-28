#ifndef __EMULATORLIB__ALU__H
#define __EMULATORLIB__ALU__H
#include <cstdint>
#include "register.h"
#include "clock.h"

namespace EmulatorLib {
	class ALU
	{
	private:
		 bool isSubtracting_ = false;
		 const EmulatorLib::Register &A_, &B_;
		 bool CF_ = false;
		 bool ZF_ = false;
	public:
		ALU(const EmulatorLib::Register &A, const EmulatorLib::Register &B);
		std::uint8_t out();
		bool cf();
		bool zf();
		void substract();
	};
} // namespace EmulatorLib

#endif

