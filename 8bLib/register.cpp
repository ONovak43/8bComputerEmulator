#include "register.h"
#include <iostream>

std::uint8_t EmulatorLib::Register::out() const
{
	return value_;
}

void EmulatorLib::Register::load(std::uint8_t value)
{
	value_ = std::move(value);
}

void EmulatorLib::Register::clear()
{
	load(0);
}

EmulatorLib::Register EmulatorLib::Register::operator=(std::uint8_t value)
{
	this->load(value);
	return *this;
}
