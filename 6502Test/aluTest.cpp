#include <memory>
#include "pch.h"
#include "../8bComputerEmulator/alu.cpp"
#include "../8bComputerEmulator/register.cpp"

namespace {
	class ALUTest : public ::testing::Test
	{
	protected:
		void SetUp() override
		{
			alu = std::make_unique<EmulatorLib::ALU>(EmulatorLib::ALU(A, B));
		}

		std::unique_ptr<EmulatorLib::ALU> alu;
		EmulatorLib::Register A;
		EmulatorLib::Register B;
	};

	TEST_F(ALUTest, ALUShouldReturnZeroIfRegistersAreCleared) {
		A.clear();
		B.clear();
		EXPECT_EQ(alu->value(), 0);
	}

	TEST_F(ALUTest, ALUShouldReturnOneIfARegisterIsOneAndBRegisterIsZero) {
		A = 1;
		B = 0;
		EXPECT_EQ(alu->value(), 1);
	}

	TEST_F(ALUTest, ALUShouldReturnFifteenIfARegisterIsTenAndBRegisterIsFive) {
		A = 10;
		B = 5;
		EXPECT_EQ(alu->value(), 15);
	}

	TEST_F(ALUTest, ALUShouldStartFromZeroIfItOverflow) {
		A = UCHAR_MAX;
		B = 30;
		EXPECT_EQ(alu->value(), 30);
	}

	TEST_F(ALUTest, ALUShouldReturnZeroIfItsSubtractingAndRegistersAreCleared) {
		A.clear();
		B.clear();
		alu->substract();
		EXPECT_EQ(alu->value(), 0);
	}

	TEST_F(ALUTest, ALUShouldReturnOneIfItsSubtractingAndARegisterIsOneAndBRegisterIsZero) {
		A = 1;
		B = 0;
		alu->substract();
		EXPECT_EQ(alu->value(), 1);
	}

	TEST_F(ALUTest, ALUShouldReturnTenIfItsSubtractingAndARegisterIstenAndBRegisterIsFive) {
		A = 10;
		B = 5;
		alu->substract();
		EXPECT_EQ(alu->value(), 5);
	}

	TEST_F(ALUTest, ALUShouldReturnSumOfRegisterAAndBIfItsSubtractingAndThenAdding) {
		A = 10;
		B = 5;
		alu->substract();
		EXPECT_EQ(alu->value(), 5);
		EXPECT_EQ(alu->value(), 15);
	}
}