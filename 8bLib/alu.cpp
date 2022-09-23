#include "alu.h"

EmulatorLib::ALU::ALU(const EmulatorLib::Register &A, const EmulatorLib::Register &B)
	: A_{A}, B_{B}
{
}

std::uint8_t EmulatorLib::ALU::out()
{
	if (isSubtracting_)
	{
		isSubtracting_ = false;
		return A_.out() - B_.out();
	}

	int value = A_.out() + B_.out();

	if (value > 255) { 
		value -= 255; // overflow, reg. value shoud not be > 510
	}

	return value;
}

void EmulatorLib::ALU::substract()
{
	isSubtracting_ = true;
}