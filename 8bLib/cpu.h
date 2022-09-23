#ifndef __EMULATORLIB__CPU__H
#define __EMULATORLIB__CPU__H
#include <cstdint>
#include "register.h"
#include "shortRegister.h"
#include "programCounter.h"
#include "alu.h"
#include "instructionRegister.h"
#include "ram.h"

namespace EmulatorLib {
	class CPU
	{
	public:
		CPU();
		void Reset();
		void Execute();
	private:
		EmulatorLib::Register A_, B_; // Registers A and B
		EmulatorLib::InstructionRegister IR_; // Instruction Register
		EmulatorLib::ShortRegister MAR_; // Memory Address Register
		EmulatorLib::ProgramCounter PC_; // Program Counter
		EmulatorLib::ALU ALU_; // ALU
		EmulatorLib::RAM ram; // RAM
	};
} // namespace Emulator
#endif

