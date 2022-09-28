#include "shortRegister.h"
#include <iostream>

EmulatorLib::ShortRegister EmulatorLib::ShortRegister::operator=(std::uint8_t value)
{
	this->load(value);
	return *this;
}

std::uint8_t EmulatorLib::ShortRegister::out() const
{
	return value_ & 0b00001111;
}