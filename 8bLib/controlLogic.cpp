#include "controlLogic.h"

EmulatorLib::ControlLogic::ControlLogic(EmulatorLib::Register& A, EmulatorLib::Register& B,
	EmulatorLib::InstructionRegister& IR, EmulatorLib::ShortRegister& MAR, 
	EmulatorLib::ProgramCounter& PC, EmulatorLib::ALU& ALU,
	EmulatorLib::RAM& RAM, EmulatorLib::Clock& clock)
	: A_{A}, B_{B}, IR_{IR}, MAR_{MAR},
	PC_{PC}, ALU_{ALU}, RAM_{RAM}, clk_{clock}
{
}

void EmulatorLib::ControlLogic::Execute(std::uint8_t ins)
{
	switch ((Instruction)ins)
	{
	case Instruction::NOP:
		clk_.tick();
		break;
	default:
		std::stringstream ss;
		ss << std::hex << ((int)ins);
		std::string s;
		ss >> s;
		s = "Instruction 0x" + s + " does not exist.";
		const char* msg = s.c_str();

		throw EmulatorLib::ForbiddenActionException(msg);
	}
}
