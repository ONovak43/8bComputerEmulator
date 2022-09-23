#include <iostream>
#include "register.h"
#include "alu.h"
#include "ram.h"

int main()
{
	EmulatorLib::RAM ram;
	ram.loadAt(0x0, 0x5);
}