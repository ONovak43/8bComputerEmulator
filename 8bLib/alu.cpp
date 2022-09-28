#include "alu.h"

EmulatorLib::ALU::ALU(const EmulatorLib::Register& A, const EmulatorLib::Register& B)
	: A_{ A }, B_{ B }
{
}

std::uint8_t EmulatorLib::ALU::out()
{
	int ret = A_.out() + B_.out();

	if (isSubtracting_)
	{
		isSubtracting_ = false;
		ret = A_.out() - B_.out();
	} 
	
	if (ret > 255) {
		ret -= 255; // overflow, reg. value shoud not be > 510
	}

	return ret;
}

bool EmulatorLib::ALU::cf()
{
	return (A_.out() + B_.out()) > 255;
}

bool EmulatorLib::ALU::zf()
{
	int value = 0;

	if (isSubtracting_) {
		value = A_.out() - B_.out();
	}
	else {
		value = A_.out() + B_.out();
	}

	return value == 0;
}

void EmulatorLib::ALU::substract()
{
	isSubtracting_ = true;
}