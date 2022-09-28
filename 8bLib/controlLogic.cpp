#include "controlLogic.h"

EmulatorLib::ControlLogic::ControlLogic(EmulatorLib::Register& A, EmulatorLib::Register& B, EmulatorLib::Register& OUT,
	EmulatorLib::InstructionRegister& IR, EmulatorLib::ShortRegister& MAR, 
	EmulatorLib::ProgramCounter& PC, EmulatorLib::ALU& ALU,
	EmulatorLib::RAM& RAM, EmulatorLib::Clock& clock)
	: A_{A}, B_{B}, OUT_{OUT}, IR_{IR}, MAR_{MAR},
	PC_{PC}, ALU_{ALU}, RAM_{RAM}, clk_{clock}
{
}

void EmulatorLib::ControlLogic::execute(EmulatorLib::ControlLogic::Instruction instruction, std::uint8_t data)
{
	switch (instruction)
	{
	case Instruction::NOP:
		clk_.tick();
		break;
	case Instruction::LDA:
		MAR_.load(data);
		A_ = RAM_.dataAt(MAR_.out());
		clk_.tick(3);
		break;
	case Instruction::ADD:
		MAR_.load(data);
		B_ = RAM_.dataAt(MAR_.out());
		A_ = ALU_.out();
		clk_.tick(4);
		break;
	case Instruction::SUB:
		MAR_.load(data);
		B_ = RAM_.dataAt(MAR_.out());
		ALU_.substract();
		A_ = ALU_.out();
		clk_.tick(4);
		break;
	case Instruction::STA:
		MAR_.load(data);
		RAM_.loadAt(MAR_.out(), A_.out());
		clk_.tick(3);
		break;
	case Instruction::LDI:
		A_ = data;
		clk_.tick(2);
		break;
	case Instruction::JMP:
		PC_.load(data);
		clk_.tick(2);
		break;
	case Instruction::JC:
		if (ALU_.cf()) {
			PC_.load(data);
			clk_.tick();
		}
		clk_.tick();
		break;
	case Instruction::JZ:
		if (ALU_.zf()) {
			PC_.load(data);
			clk_.tick();
		}
		clk_.tick();
		break;
	case Instruction::OUT:
		OUT_ = A_.out();
		clk_.tick(2);
		break;
	case Instruction::HLT:
		HALT = true;
		break;
	default:
		std::stringstream ss;
		ss << std::hex << ((int)instruction);
		std::string s;
		ss >> s;
		s = "Instruction 0x" + s + " does not exist.";
		const char* msg = s.c_str();

		throw EmulatorLib::ForbiddenActionException(msg);
	}
}