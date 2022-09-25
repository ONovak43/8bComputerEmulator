#include "pch.h"
#include "../8bLib/clock.cpp"

TEST(ClockTest, CyclesShoudBeZeroByDefault)
{
	EmulatorLib::Clock clk;
	EXPECT_EQ(clk.remaining(), 0);
}
TEST(ClockTest, ClockShouldTickExactlyThatManyTimesItsSetToAndThenThrowAnException)
{
	EmulatorLib::Clock clk;

	clk.set(10);
	for (int i = 0; i < 10; i++) { 
		clk.tick(); // Tick 10 times
	}

	EXPECT_THROW(clk.tick(), EmulatorLib::ForbiddenActionException);
}