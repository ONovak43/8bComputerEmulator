#ifndef __EMULATORLIB__CPU__H
#define __EMULATORLIB__CPU__H
#include <cstdint>
#include "register.h"
#include "shortRegister.h"
#include "programCounter.h"
#include "alu.h"
#include "instructionRegister.h"
#include "ram.h"
#include "controlLogic.h"

namespace EmulatorLib {
	class CPU
	{
	public:
		CPU();
		void reset();
		void execute(std::int32_t cycles);
		void loadToMemory(std::array<std::uint8_t, 16> image);
		std::uint8_t out();
	private:
		EmulatorLib::Register A_, B_; // Registers A and B
		EmulatorLib::Register OUT_; // Output Register
		EmulatorLib::InstructionRegister IR_; // Instruction Register
		EmulatorLib::ShortRegister MAR_; // Memory Address Register
		EmulatorLib::ProgramCounter PC_; // Program Counter
		EmulatorLib::ALU ALU_; // ALU
		EmulatorLib::RAM RAM_; // RAM
		EmulatorLib::ControlLogic CL_;
		EmulatorLib::Clock clk_;
		std::uint8_t fetchFromMemory();
		std::pair<EmulatorLib::ControlLogic::Instruction, std::uint8_t> fetchInstruction(std::uint8_t instruction);
	};
} // namespace Emulator
#endif

