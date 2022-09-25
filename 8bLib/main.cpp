#include <iostream>
#include "register.h"
#include "alu.h"
#include "ram.h"
#include "clock.h"
#include "cpu.h"

int main()
{
	EmulatorLib::CPU cpu;
	try {
		cpu.Execute();
	}
	catch (const std::exception& ex)
	{
		std::cerr << ex.what() << "\n";
	}
}