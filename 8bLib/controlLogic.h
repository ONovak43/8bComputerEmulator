#ifndef __EMULATORLIB__CONTROLLOGIC__H
#define __EMULATORLIB__CONTROLLOGIC__H
#include <cstdint>
#include <sstream>
#include <utility>
#include "forbiddenActionException.h"
#include "clock.h"
#include "register.h"
#include "instructionRegister.h"
#include "shortRegister.h"
#include "programCounter.h"
#include "alu.h"
#include "ram.h"

namespace EmulatorLib {
	class ControlLogic
	{
	public:
		const enum class Instruction : std::uint8_t {
			NOP = 0x0,
			LDA = 0x1,
			ADD = 0x2,
			SUB = 0x3,
			STA = 0x4,
			LDI = 0x5,
			JMP = 0x6,
			JC = 0x7,
			JZ = 0x8,
			OUT = 0xE,
			HLT = 0xF,
		};
		ControlLogic(EmulatorLib::Register& A, EmulatorLib::Register& B, 
			EmulatorLib::InstructionRegister& IR, EmulatorLib::ShortRegister& MAR,
			EmulatorLib::ProgramCounter& PC, EmulatorLib::ALU& ALU,
			EmulatorLib::RAM& RAM, EmulatorLib::Clock& clock);

		void execute(EmulatorLib::ControlLogic::Instruction instruction, std::uint8_t data = 0x0);
	private:
		EmulatorLib::Register& A_;
		EmulatorLib::Register& B_;
		EmulatorLib::InstructionRegister& IR_;
		EmulatorLib::ShortRegister& MAR_;
		EmulatorLib::ProgramCounter& PC_;
		EmulatorLib::ALU& ALU_;
		EmulatorLib::RAM& RAM_;
		EmulatorLib::Clock& clk_;	
	};
}

#endif

