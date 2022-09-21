#ifndef __EMULATORLIB__SHORTREGISTER__H
#define __EMULATORLIB__SHORTREGISTER__H
#include "register.h"


namespace EmulatorLib {
	// 4 bit register (always returns 4 LSB bits) 
	class ShortRegister
		: public EmulatorLib::Register
	{
	public:
		using Register::value;
		EmulatorLib::ShortRegister operator=(std::uint8_t value);
		std::uint8_t value() const override;
	};
} // namespace EmulatorLib
#endif
