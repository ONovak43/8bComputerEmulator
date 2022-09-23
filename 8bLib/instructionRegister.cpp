#include "instructionRegister.h"

std::uint8_t EmulatorLib::InstructionRegister::out() const
{
    return value_ & 0b00001111;
}

std::uint8_t EmulatorLib::InstructionRegister::address()
{
    return value_ & 0b11110000;
}

std::uint8_t EmulatorLib::InstructionRegister::data()
{
    return value_ & 0b00001111;
}
