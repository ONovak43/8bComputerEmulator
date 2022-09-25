#ifndef __EMULATORLIB__CLOCK__H
#define __EMULATORLIB__CLOCK__H

#include <cstdint>
#include "forbiddenActionException.h"

namespace EmulatorLib {
	class Clock
	{
	public:
		Clock();
		void set(std::int32_t cycles);
		void tick(std::int32_t times = 1);
		std::int32_t remaining();
	private:
		std::int32_t cycles_;
	};
}
#endif

