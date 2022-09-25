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
	CL_.Execute(0x0);
}
