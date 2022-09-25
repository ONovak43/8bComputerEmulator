#ifndef __EMULATORLIB__CLOCK__H
#define __EMULATORLIB__CLOCK__H

#include <cstdint>
#include <functional>
#include "forbiddenActionException.h"
#include <vector>

namespace EmulatorLib {
	class Clock
	{
	public:
		Clock();
		void set(std::int32_t cycles);
		void tick(std::int32_t times = 1);
		void onNextTick(std::function<void()>&& callback);
		std::int32_t remaining();
	private:
		std::int32_t cycles_;
		std::vector<std::function<void()>> callbacks_;
	};
}
#endif

