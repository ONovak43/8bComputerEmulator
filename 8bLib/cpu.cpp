#include "cpu.h"

EmulatorLib::CPU::CPU()
	: ALU_(A_, B_, clk_), CL_(A_, B_, IR_, MAR_, PC_, ALU_, RAM_, clk_)
{
}

void EmulatorLib::CPU::Reset()
{
	A_.clear();
	B_.clear();
	IR_.clear();
	MAR_.clear();
	PC_.clear();
	RAM_.clear();
}

void EmulatorLib::CPU::Execute()
{
	clk_.set(1);
	auto instruction = fetchInstruction(fetchFromMemory()); // fetch cycle
	CL_.execute(instruction.first, instruction.second);
}

std::uint8_t EmulatorLib::CPU::fetchFromMemory()
{
	MAR_.load(PC_.out());
	clk_.tick();
	return MAR_.out();
}

std::pair<EmulatorLib::ControlLogic::Instruction, std::uint8_t> EmulatorLib::CPU::fetchInstruction(std::uint8_t instruction)
{
	using EmulatorLib::ControlLogic;
	auto ramData = RAM_.dataAt(instruction);
	IR_.load(ramData);
	PC_.increase();
	clk_.tick();
	return std::make_pair(((ControlLogic::Instruction)(IR_.address())), IR_.data());
}

