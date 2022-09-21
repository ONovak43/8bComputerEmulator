#include <iostream>
#include "register.h"
#include "alu.h"
#include "shortRegister.h"

int main()
{
	EmulatorLib::ShortRegister A;
	A = 0b101;
	A.value();
	std::cout << "TEST";
}