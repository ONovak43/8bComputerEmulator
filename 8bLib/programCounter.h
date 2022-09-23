#ifndef __EMULATORLIB__PROGRAMCOUNTER__H
#define __EMULATORLIB__PROGRAMCOUNTER__H
#include "shortRegister.h"

namespace EmulatorLib {
	class ProgramCounter 
		: public EmulatorLib::ShortRegister
	{
	public:
		void increase();
	};
}
#endif

