#include "ram.h"
#include "forbiddenActionException.h"

EmulatorLib::RAM::RAM() :
	memory{}
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

	return memory[address];
}

void EmulatorLib::RAM::loadAt(std::uint8_t address, std::uint8_t data)
{
	try {
		checkAddress(address);
	}
	catch (EmulatorLib::ForbiddenActionException) {
		throw;
	}

	memory[address] = data;
}

void EmulatorLib::RAM::checkAddress(std::uint8_t address)
{
	if (memory.max_size() <= address) {
		std::stringstream ss;
		ss << std::hex << address;
		std::string s;
		ss >> s;
		s = "Address" + s + "does not exist.";

		const char* msg = s.c_str();

		throw ForbiddenActionException(msg);
	}
}

void EmulatorLib::RAM::clear()
{
	memory.fill({});
}
