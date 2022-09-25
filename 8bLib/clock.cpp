#include "clock.h"

EmulatorLib::Clock::Clock() 
	: cycles_{ 0 }
{
}

void EmulatorLib::Clock::set(std::int32_t cycles)
{
	cycles_ = cycles;
}

void EmulatorLib::Clock::tick(std::int32_t times)
{
	if ((cycles_ - times) < 0) {
		throw EmulatorLib::ForbiddenActionException("Clocks does not have more ticks.");
	}

	cycles_ -= times;
}

std::int32_t EmulatorLib::Clock::remaining()
{
	return cycles_;
}
