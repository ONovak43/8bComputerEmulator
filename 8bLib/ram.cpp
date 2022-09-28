#include "ram.h"
#include "forbiddenActionException.h"

EmulatorLib::RAM::RAM() :
	memory_{}
{

}

std::uint8_t EmulatorLib::RAM::dataAt(std::uint8_t address)
{
	try {
		checkAddress(address);
	}
	catch (EmulatorLib::ForbiddenActionException) {
		throw;
	}

	return memory_[address];
}

void EmulatorLib::RAM::loadAt(std::uint8_t address, std::uint8_t data)
{
	try {
		checkAddress(address);
	}
	catch (EmulatorLib::ForbiddenActionException) {
		throw;
	}

	memory_[address] = data;
}

void EmulatorLib::RAM::loadImage(std::array<std::uint8_t, 16> image)
{
	memory_ = image;
}

void EmulatorLib::RAM::checkAddress(std::uint8_t address)
{
	if (memory_.max_size() <= address) {
		std::stringstream ss;
		ss << std::hex << ((int)address);
		std::string s;
		ss >> s;
		s = "Address 0x" + s + " does not exist.";

		const char* msg = s.c_str();

		throw ForbiddenActionException(msg);
	}
}

void EmulatorLib::RAM::clear()
{
	memory_.fill({});
}
