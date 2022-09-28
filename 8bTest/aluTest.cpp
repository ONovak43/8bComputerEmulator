#include <memory>
#include "pch.h"
#include "../8bLib/alu.cpp"
#include "../8bLib/register.cpp"

namespace {
	class ALUTest : public ::testing::Test
	{
	protected:
		void SetUp() override
		{
			alu = std::make_unique<EmulatorLib::ALU>(A, B);
		}

		std::unique_ptr<EmulatorLib::ALU> alu;
		EmulatorLib::Register A;
		EmulatorLib::Register B;
		EmulatorLib::Clock clk;
	};

	TEST_F(ALUTest, ALUShouldReturnZeroIfRegistersAreCleared) {
		A.clear();
		B.clear();
		EXPECT_EQ(alu->out(), 0);
	}

	TEST_F(ALUTest, ALUShouldReturnOneIfARegisterIsOneAndBRegisterIsZero) {
		A = 1;
		B = 0;
		EXPECT_EQ(alu->out(), 1);
	}

	TEST_F(ALUTest, ALUShouldReturnFifteenIfARegisterIsTenAndBRegisterIsFive) {
		A = 10;
		B = 5;
		EXPECT_EQ(alu->out(), 15);
	}

	TEST_F(ALUTest, ALUShouldStartFromZeroWhenItOverflowsAndCarryFlagShouldBeSetToTrue) {
		A = UCHAR_MAX;
		B = 30;
		EXPECT_EQ(alu->out(true), 30);
		EXPECT_TRUE(alu->cf());
	}

	TEST_F(ALUTest, ALUShouldSetCarryFlagToTrueWhenSubtractingRegistersAAndBAndResultIsPositive) {
		A = 40;
		B = 30;
		alu->substract();
		EXPECT_EQ(alu->out(true), 10);
		EXPECT_TRUE(alu->cf());
	}

	TEST_F(ALUTest, ALUShouldSetCarryFlagToTrueWhenSubtractingRegistersAAndBAndResultIsNegative) {
		A = 10;
		B = 30;
		alu->substract();
		EXPECT_EQ(alu->out(true), 236);
		EXPECT_FALSE(alu->cf());
	}

	TEST_F(ALUTest, ALUShouldReturnZeroIfItsSubtractingAndRegistersAreCleared) {
		A.clear();
		B.clear();
		alu->substract();
		EXPECT_EQ(alu->out(), 0);
	}

	TEST_F(ALUTest, ALUShouldReturnOneIfItsSubtractingAndARegisterIsOneAndBRegisterIsZero) {
		A = 1;
		B = 0;
		alu->substract();
		EXPECT_EQ(alu->out(), 1);
	}

	TEST_F(ALUTest, ALUShouldReturnTenIfItsSubtractingAndARegisterIstenAndBRegisterIsFive) {
		A = 10;
		B = 5;
		alu->substract();
		EXPECT_EQ(alu->out(), 5);
	}

	TEST_F(ALUTest, ALUShouldReturnSumOfRegisterAAndBIfItsSubtractingAndThenAdding) {
		A = 10;
		B = 5;
		alu->substract();
		EXPECT_EQ(alu->out(), 5);
		EXPECT_EQ(alu->out(), 15);
	}
}