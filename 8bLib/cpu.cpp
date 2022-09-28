#include "cpu.h"
#include <iostream>

EmulatorLib::CPU::CPU()
	: ALU_(A_, B_), CL_(A_, B_, OUT_, IR_, MAR_, PC_, ALU_, RAM_, clk_)
{
}

void EmulatorLib::CPU::reset()
{
	CL_.HALT = false;
	A_.clear();
	B_.clear();
	OUT_.clear();
	IR_.clear();
	MAR_.clear();
	PC_.clear();
	RAM_.clear();
}

void EmulatorLib::CPU::execute(std::int32_t cycles)
{
	clk_.set(cycles);
	while (clk_.remaining() > 0 && CL_.HALT == false) {
		auto instruction = fetchInstruction(fetchFromMemory()); // fetch cycle
		CL_.execute(instruction.first, instruction.second);
	}
}

void EmulatorLib::CPU::loadToMemory(std::array<std::uint8_t, 16> image)
{
	RAM_.loadImage(image);
}

std::uint8_t EmulatorLib::CPU::out()
{
	return OUT_.out();
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

