#include "alu.h"

EmulatorLib::ALU::ALU(const EmulatorLib::Register& A, const EmulatorLib::Register& B, EmulatorLib::Clock& clk)
	: A_{ A }, B_{ B }, clk_{clk}
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
		CF_ = true;
	}

	return value;
}

bool EmulatorLib::ALU::cf()
{
	clk_.onNextTick([this]() {
		this->CF_ = false;
	});

	return CF_;
}

bool EmulatorLib::ALU::zf()
{
	return true;
}

void EmulatorLib::ALU::substract()
{
	isSubtracting_ = true;
}