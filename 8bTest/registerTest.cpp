#include <memory>
#include "pch.h"
#include "../8bLib/register.h"
#include "../8bLib/shortRegister.cpp"
#include "../8bLib/bus.cpp"
#include "../8bLib/forbiddenActionException.cpp"
#include "../8bLib/programCounter.cpp"
#include "../8bLib/programCounter.h"

namespace {
	TEST(RegisterTest, RegisterShouldBeZeroWhenItsCleared)
	{
		EmulatorLib::Register A;
		A.clear();
		EXPECT_EQ(A.out(), 0);

		A = 5;
		A.clear();
		EXPECT_EQ(A.out(), 0);
	}

	TEST(RegisterTest, RegisterShouldContainAValueThatsSetTo)
	{
		EmulatorLib::Register A;
		A = 5;
		EXPECT_EQ(A.out(), 5);

		A = 255;
		EXPECT_EQ(A.out(), 255);
	}

	TEST(RegisterTest, RegisterShouldOverflowWhenItsSetToGreaterNumberThan255)
	{
		EmulatorLib::Register A;
		A = 256;
		EXPECT_EQ(A.out(), 0);
	}

	TEST(ShortRegisterTest, ShortRegisterShouldBeZeroWhenItsCleared)
	{
		EmulatorLib::ShortRegister A;
		A.clear();
		EXPECT_EQ(A.out(), 0);
	}

	TEST(ShortRegisterTest, ShortRegisterShouldContainAValueThatsSetTo)
	{
		EmulatorLib::ShortRegister A;
		A = 5;
		EXPECT_EQ(A.out(), 5);

		A = 1;
		EXPECT_EQ(A.out(), 1);
	}

	TEST(ShortRegisterTest, ShortRegisterShouldReturnOnlyFourLastBits)
	{
		EmulatorLib::ShortRegister A;

		A = 0b01011111;
		EXPECT_EQ(A.out(), 0b1111);
	}

	TEST(BUSTest, BUSShouldThrowAnExceptionWhenItsCleared)
	{
		EmulatorLib::BUS bus;

		EXPECT_THROW(bus.clear(), EmulatorLib::ForbiddenActionException);
	}

	TEST(BUSTest, BUSShouldReturnAValueItsSetTo)
	{
		EmulatorLib::BUS bus;

		bus.load(5);

		EXPECT_EQ(bus.out(), 5);
	}

	TEST(ProgramCounterTest, PCShouldIncreaseItsValue)
	{
		EmulatorLib::ProgramCounter pc;

		pc.clear();
		pc.increase();

		EXPECT_EQ(pc.out(), 1);
	}

	TEST(ProgramCounterTest, PCShouldLoadAValue)
	{
		EmulatorLib::ProgramCounter pc;

		pc.load(5);

		EXPECT_EQ(pc.out(), 5);
	}
}
