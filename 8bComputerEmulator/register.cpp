#include "register.h"
#include <iostream>

std::uint8_t EmulatorLib::Register::value() const
{
	return value_;
}

void EmulatorLib::Register::value(std::uint8_t value)
{
	value_ = std::move(value);
}

void EmulatorLib::Register::clear()
{
	value(0);
}

EmulatorLib::Register EmulatorLib::Register::operator=(std::uint8_t value)
{
	this->value(value);
	return *this;
}
