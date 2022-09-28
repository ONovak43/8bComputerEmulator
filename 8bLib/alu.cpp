#include "alu.h"

EmulatorLib::ALU::ALU(const EmulatorLib::Register& A, const EmulatorLib::Register& B)
	: A_{ A }, B_{ B }
{
}

std::uint8_t EmulatorLib::ALU::out(const bool FI)
{
	int ret = A_.out() + B_.out();

	if (isSubtracting_)
	{
		isSubtracting_ = false;
		ret = A_.out() - B_.out();
		CF_ = (FI && ret >= 0); // set carry flag if FI = true AND ret >= 0 (subtracting)
	} else if (FI && ret > 255) { // set carry flag if FI = true AND ret > 255 (adding)
		CF_ = true;
	}

	ZF_ = (FI && ret == 0);

	if (ret > 255) {
		ret -= 255; // overflow, reg. value shoud not be > 510
	}

	return ret;
}

bool EmulatorLib::ALU::cf()
{
	return CF_;
}

bool EmulatorLib::ALU::zf()
{
	return ZF_;
}

void EmulatorLib::ALU::substract()
{
	isSubtracting_ = true;
}