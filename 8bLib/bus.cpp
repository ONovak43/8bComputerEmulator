#include "bus.h"

void EmulatorLib::BUS::clear()
{
	throw EmulatorLib::ForbiddenActionException("BUS cannot be cleared.");
}
