#ifndef __EMULATORLIB__CPU__H
#define __EMULATORLIB__CPU__H
#include <cstdint>
#include "register.h"
#include "shortRegister.h"
#include "alu.h"

namespace EmulatorLib {
	class CPU
	{
	public:
		CPU();
		void Reset();
		void Execute();
		void Clock();
	private:
		EmulatorLib::Register A_, B_; // Registers A and B
		EmulatorLib::ShortRegister MAR_; // Memory Address Register
		EmulatorLib::ShortRegister PC_; // Program Counter
		EmulatorLib::ShortRegister IR_; // Instruction Register
		EmulatorLib::ALU ALU_;
		std::uint8_t Clock_ : 1;
	};
} // namespace Emulator
#endif

