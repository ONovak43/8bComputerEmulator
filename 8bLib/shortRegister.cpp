#include "shortRegister.h"
#include <iostream>

EmulatorLib::ShortRegister EmulatorLib::ShortRegister::operator=(std::uint8_t value)
{
	this->load(value);
	return *this;
}

std::uint8_t EmulatorLib::ShortRegister::out() const
{
	std::cout << (value_ & 0b00001111);
	return value_ & 0b00001111;
}