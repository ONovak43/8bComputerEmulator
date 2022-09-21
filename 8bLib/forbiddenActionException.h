#ifndef __EMULATORLIB__FORBIDDENACTIONECEPTION__H
#define __EMULATORLIB__FORBIDDENACTIONECEPTION__H
#include <exception>

namespace EmulatorLib {
	class ForbiddenActionException : public std::exception
	{
	private:
		char* msg_;
	public:
		ForbiddenActionException(char const* const message) throw();
	};
}
#endif

