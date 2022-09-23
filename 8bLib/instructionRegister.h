#ifndef __EMULATORLIB__INSTRUCTIONREGISTER__H
#define __EMULATORLIB__INSTRUCTIONREGISTER__H

#include <cstdint>
#include "register.h"
#include "forbiddenActionException.h"

namespace EmulatorLib {
	class InstructionRegister
		: public EmulatorLib::Register
	{
	public:
		std::uint8_t out() const override final;
		std::uint8_t address();
		std::uint8_t data();
	};
}

#endif
