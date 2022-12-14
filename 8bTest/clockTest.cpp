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

TEST(ClockTest, ClockShouldExecuteActionOnNextTickIfThatActionIsSet)
{
	EmulatorLib::Clock clk;
	bool a = false;
	clk.set(2);

	clk.onNextTick([&a]() {
		a = true;
	});

	EXPECT_FALSE(a);
	clk.tick();
	EXPECT_TRUE(a);
	clk.tick();
	EXPECT_TRUE(a);
}