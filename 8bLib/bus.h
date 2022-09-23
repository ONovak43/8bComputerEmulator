#ifndef __EMULATORLIB__BUS__H
#define __EMULATORLIB__BUS__H

#include <cstdint>
#include <system_error>
#include "register.h"
#include "forbiddenActionException.h"

namespace EmulatorLib {
	class BUS :
		public EmulatorLib::Register
	{
	public:
		void clear() override final;
	};
}
#endif
