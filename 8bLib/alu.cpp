#include "alu.h"

EmulatorLib::ALU::ALU(const EmulatorLib::Register &A, const EmulatorLib::Register &B)
	: A_{A}, B_{B}
{
}

std::uint8_t EmulatorLib::ALU::value()
{
	if (isSubtracting_)
	{
		isSubtracting_ = false;
		return A_.value() - B_.value();
	}

	int value = A_.value() + B_.value();

	if (value > 255) { 
		value -= 255; // overflow, reg. value shoud not be > 510
	}

	return value;
}

void EmulatorLib::ALU::substract()
{
	isSubtracting_ = true;
}