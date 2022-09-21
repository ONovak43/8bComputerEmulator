#ifndef __EMULATORLIB__ALU__H
#define __EMULATORLIB__ALU__H
#include <cstdint>
#include "register.h"

namespace EmulatorLib {
	class ALU
	{
	private:
		 bool isSubtracting_ = false;
		 const EmulatorLib::Register &A_, &B_;
	public:
		ALU(const EmulatorLib::Register &A, const EmulatorLib::Register &B);
		std::uint8_t value();
		void substract();
	};
} // namespace EmulatorLib

#endif

