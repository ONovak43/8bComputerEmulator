#ifndef __EMULATORLIB__REGISTER__H
#define __EMULATORLIB__REGISTER__H

#include <cstdint>
#include <utility>

namespace EmulatorLib {
	class Register
	{
	protected:
		std::uint8_t value_ = 0;
	public:
		virtual std::uint8_t out() const;
		virtual void load(std::uint8_t value);
		virtual void clear();
		EmulatorLib::Register operator=(std::uint8_t value);
	};
}
#endif

