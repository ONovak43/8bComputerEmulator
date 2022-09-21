#include <memory>
#include "pch.h"
#include "../8bComputerEmulator/register.h"
#include "../8bComputerEmulator/shortRegister.cpp"

namespace {
	TEST(RegisterTest, RegisterShouldBeZeroWhenItsCleared)
	{
		EmulatorLib::Register A;
		A.clear();
		EXPECT_EQ(A.value(), 0);

		A = 5;
		A.clear();
		EXPECT_EQ(A.value(), 0);
	}

	TEST(RegisterTest, RegisterShouldContainAValueThatsSetTo)
	{
		EmulatorLib::Register A;
		A = 5;
		EXPECT_EQ(A.value(), 5);

		A = 255;
		EXPECT_EQ(A.value(), 255);
	}

	TEST(RegisterTest, RegisterShouldOverflowWhenItsSetToGreaterNumberThan255)
	{
		EmulatorLib::Register A;
		A = 256;
		EXPECT_EQ(A.value(), 0);
	}

	TEST(ShortRegisterTest, ShortRegisterShouldBeZeroWhenItsCleared)
	{
		EmulatorLib::ShortRegister A;
		A.clear();
		EXPECT_EQ(A.value(), 0);
	}

	TEST(ShortRegisterTest, ShortRegisterShouldContainAValueThatsSetTo)
	{
		EmulatorLib::ShortRegister A;
		A = 5;
		EXPECT_EQ(A.value(), 5);

		A = 1;
		EXPECT_EQ(A.value(), 1);
	}

	TEST(ShortRegisterTest, ShortRegisterShouldReturnOnlyFourLastBits)
	{
		EmulatorLib::ShortRegister A;

		A = 0b01011111;
		EXPECT_EQ(A.value(), 0b1111);
	}
}
