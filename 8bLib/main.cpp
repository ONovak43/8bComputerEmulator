#include <iostream>
#include "register.h"
#include "alu.h"
#include "ram.h"
#include "clock.h"
#include "cpu.h"

int main()
{
	const std::uint8_t
		NOP = (0x0 << 4),
		LDA = (0x1 << 4),
		ADD = (0x2 << 4),
		SUB = (0x3 << 4),
		STA = (0x4 << 4),
		LDI = (0x5 << 4),
		JMP = (0x6 << 4),
		JC  = (0x7 << 4),
		JZ  = (0x8 << 4),
		OUT = (0xE << 4),
		HLT = (0xF << 4);

	EmulatorLib::CPU cpu;
	std::array<std::uint8_t, 16> image = {
		LDA + 0xE,	// LDA 0xE
		SUB + 0xC,	// SUB 0xC
		JC  + 0x6,	// JC 0x6 
		LDA + 0xD,	// LDA 0xD
		OUT,		// OUT
		HLT,		// HALT
		STA + 0xE,	// STA 0xE
		LDA + 0xD,	// LDA 0xD
		ADD + 0xF,	// ADD 0xF
		STA + 0xD,	// STA 0xD
		JMP + 0x0,	// JMP 0x0
		0x0,
		0x1,
		0x0,
		0x7,
		0x8,
	};

	try {
		cpu.reset();
		cpu.loadToMemory(image);
		cpu.execute(10000);
		std::cout << "OUT: " << (int)cpu.out();
	}
	catch (const EmulatorLib::ForbiddenActionException& ex)
	{
		std::cerr << ex.what() << "\n";
	}
}