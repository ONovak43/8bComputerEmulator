#include <memory>
#include "pch.h"
#include "../8bLib/controlLogic.cpp"
#include "../8bLib/register.h"
#include "../8bLib/clock.h"
#include "../8bLib/register.h"
#include "../8bLib/instructionRegister.h"
#include "../8bLib/instructionRegister.cpp"
#include "../8bLib/shortRegister.h"
#include "../8bLib/programCounter.h"
#include "../8bLib/ram.h"
#include "../8bLib/alu.h"

namespace {
	class ControlLogicInstructionsTest : public ::testing::Test
	{
	protected:
		ControlLogicInstructionsTest()
			: ALU(A, B, clk) 
		{
		}

		void SetUp() override
		{
			A.clear();
			B.clear();
			IR.clear();
			MAR.clear();
			PC.clear();
			RAM.clear();
			clk.set(0);
			cl = std::make_unique<EmulatorLib::ControlLogic>(A, B, IR, MAR, PC, ALU, RAM, clk);
		}

		std::unique_ptr<EmulatorLib::ControlLogic> cl;
		EmulatorLib::Register A, B; // Registers A and B
		EmulatorLib::InstructionRegister IR; // Instruction Register
		EmulatorLib::ShortRegister MAR; // Memory Address Register
		EmulatorLib::ProgramCounter PC; // Program Counter
		EmulatorLib::ALU ALU; // ALU
		EmulatorLib::RAM RAM; // RAM
		EmulatorLib::Clock clk;

		void TEST_RAM_NOT_AFFECTED() {
			for (int i = 0; i < 15; i++) {
				EXPECT_EQ(RAM.dataAt(i), 0);
			}
		}

		void TEST_NOT_AFFECTED() {
			TEST_RAM_NOT_AFFECTED();

			EXPECT_EQ(A.out(), 0);
			EXPECT_EQ(B.out(), 0);
			EXPECT_EQ(IR.out(), 0);
			EXPECT_EQ(MAR.out(), 0);
			EXPECT_EQ(PC.out(), 0);
			EXPECT_EQ(clk.remaining(), 0);
		}
	};

	TEST_F(ControlLogicInstructionsTest, ControlLogicShoudNotAffectAnythingWhenItDoNothing)
	{
		TEST_NOT_AFFECTED();
	}

	TEST_F(ControlLogicInstructionsTest, ControlLogicShoudThrowAnExceptionWhenInstructionDoesNotExist)
	{
		EXPECT_THROW(cl->Execute(0xFF), EmulatorLib::ForbiddenActionException);
		TEST_NOT_AFFECTED();
	}

	TEST_F(ControlLogicInstructionsTest, NOPShouldTakeOneCycleAndDoNothing)
	{
		clk.set(1);
		cl->Execute(0x0);
		TEST_NOT_AFFECTED();
	}

	TEST_F(ControlLogicInstructionsTest, LDAShouldLoadAValueToRegisterA)
	{
		clk.set(1);
		cl->Execute(0b00010001);
		EXPECT_EQ(A.out(), 1);
		EXPECT_EQ(B.out(), 0);
		EXPECT_EQ(IR.out(), 0);
		EXPECT_EQ(MAR.out(), 0);
		EXPECT_EQ(PC.out(), 0);
		EXPECT_EQ(clk.remaining(), 0);
		TEST_RAM_NOT_AFFECTED();
	}
}