#ifndef __EMULATORLIB__RAM__H
#define __EMULATORLIB__RAM__H

#include <array>
#include <cstdint>
#include <sstream>

namespace EmulatorLib {
	class RAM
	{
	public:
		RAM();
		std::uint8_t dataAt(std::uint8_t address);
		void loadAt(std::uint8_t address, std::uint8_t data);
		void clear();
		void loadImage(std::array<std::uint8_t, 15> image);
	private:
		std::array<std::uint8_t, 15> memory_;
		void checkAddress(std::uint8_t address);
		
	};
}
#endif
