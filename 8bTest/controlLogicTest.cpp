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
	class ControlLogicTest : public ::testing::Test
	{
	protected:
		ControlLogicTest()
			: ALU(A, B) 
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
			cl = std::make_unique<EmulatorLib::ControlLogic>(A, B, OUT, IR, MAR, PC, ALU, RAM, clk);
			cl->HALT = false;
		}

		std::unique_ptr<EmulatorLib::ControlLogic> cl;
		EmulatorLib::Register A, B; // Registers A and B
		EmulatorLib::Register OUT; // Output Register
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
			EXPECT_EQ(IR.address(), 0);
			EXPECT_EQ(MAR.out(), 0);
			EXPECT_EQ(PC.out(), 0);
			EXPECT_FALSE(ALU.cf());
			EXPECT_FALSE(ALU.zf());
			EXPECT_FALSE(cl->HALT);
			EXPECT_EQ(clk.remaining(), 0);
		}
	};

	TEST_F(ControlLogicTest, ControlLogicShoudNotAffectAnythingWhenItDoNothing)
	{
		TEST_NOT_AFFECTED();
	}

	TEST_F(ControlLogicTest, ControlLogicShoudThrowAnExceptionWhenInstructionDoesNotExist)
	{
		auto instruction = ((EmulatorLib::ControlLogic::Instruction)0xFF);
		EXPECT_THROW(cl->execute(instruction), EmulatorLib::ForbiddenActionException);
		TEST_NOT_AFFECTED();
	}

	TEST_F(ControlLogicTest, NOPShouldTakeOneCycleAndDoNothing)
	{
		clk.set(1);
		cl->execute(((EmulatorLib::ControlLogic::Instruction)0x0));
		TEST_NOT_AFFECTED();
	}

	TEST_F(ControlLogicTest, LDAShouldLoadAValueToRegisterA)
	{
		clk.set(2);
		auto instruction = ((EmulatorLib::ControlLogic::Instruction)0b0001);
		RAM.loadAt(0xE, 1);
		cl->execute(instruction, 0xE);

		EXPECT_EQ(A.out(), 1);
		EXPECT_EQ(B.out(), 0);
		EXPECT_EQ(IR.out(), 0);
		EXPECT_EQ(IR.address(), 0);
		EXPECT_EQ(MAR.out(), 0xE);
		EXPECT_EQ(PC.out(), 0);
		EXPECT_FALSE(ALU.cf());
		EXPECT_FALSE(ALU.zf());
		EXPECT_FALSE(cl->HALT);
		EXPECT_EQ(clk.remaining(), 0);
		for (int i = 0; i < 14; i++) {
			EXPECT_EQ(RAM.dataAt(i), 0);
		}
		EXPECT_EQ(RAM.dataAt(0xE), 1);
	}

	TEST_F(ControlLogicTest, ADDShouldAddContentOfAAndBRegistersAndSaveTheResultToRegisterA)
	{
		clk.set(3);
		auto instruction = ((EmulatorLib::ControlLogic::Instruction)0b0010);
		A = 0x3;
		RAM.loadAt(0xE, 0x4);
		cl->execute(instruction, 0xE);

		EXPECT_EQ(A.out(), 0x7);
		EXPECT_EQ(B.out(), 0x4);
		EXPECT_EQ(IR.out(), 0);
		EXPECT_EQ(IR.address(), 0);
		EXPECT_EQ(MAR.out(), 0xE);
		EXPECT_EQ(PC.out(), 0);
		EXPECT_FALSE(ALU.cf());
		EXPECT_FALSE(ALU.zf());
		EXPECT_FALSE(cl->HALT);
		EXPECT_EQ(clk.remaining(), 0);
		for (int i = 0; i < 14; i++) {
			EXPECT_EQ(RAM.dataAt(i), 0);
		}
		EXPECT_EQ(RAM.dataAt(0xE), 0x4);
	}

	TEST_F(ControlLogicTest, SUBShouldSubtractContentOfAAndBRegistersAndSaveTheResultToRegisterA)
	{
		clk.set(3);
		auto instruction = ((EmulatorLib::ControlLogic::Instruction)0b0011);
		A = 0x4;
		RAM.loadAt(0xE, 0x3);
		cl->execute(instruction, 0xE);

		EXPECT_EQ(A.out(), 0x1);
		EXPECT_EQ(B.out(), 0x3);
		EXPECT_EQ(IR.out(), 0);
		EXPECT_EQ(IR.address(), 0);
		EXPECT_EQ(MAR.out(), 0xE);
		EXPECT_EQ(PC.out(), 0);
		EXPECT_TRUE(ALU.cf());
		EXPECT_FALSE(ALU.zf());
		EXPECT_FALSE(cl->HALT);
		EXPECT_EQ(clk.remaining(), 0);
		for (int i = 0; i < 14; i++) {
			EXPECT_EQ(RAM.dataAt(i), 0);
		}
		EXPECT_EQ(RAM.dataAt(0xE), 0x3);
	}

	TEST_F(ControlLogicTest, STAShouldStoreContentOfRegisterAToMemoryOnSpecifiedAddress)
	{
		clk.set(2);
		auto instruction = ((EmulatorLib::ControlLogic::Instruction)0b0100);
		A = 0x4;
		cl->execute(instruction, 0xE);

		EXPECT_EQ(A.out(), 0x4);
		EXPECT_EQ(B.out(), 0);
		EXPECT_EQ(IR.out(), 0);
		EXPECT_EQ(IR.address(), 0);
		EXPECT_EQ(MAR.out(), 0xE);
		EXPECT_EQ(PC.out(), 0);
		EXPECT_FALSE(ALU.cf());
		EXPECT_FALSE(ALU.zf());
		EXPECT_FALSE(cl->HALT);
		EXPECT_EQ(clk.remaining(), 0);
		for (int i = 0; i < 14; i++) {
			EXPECT_EQ(RAM.dataAt(i), 0);
		}
		EXPECT_EQ(RAM.dataAt(0xE), 0x4);
	}

	TEST_F(ControlLogicTest, LDIShouldStoreAValueToRegisterA)
	{
		clk.set(1);
		auto instruction = ((EmulatorLib::ControlLogic::Instruction)0b0101);
		cl->execute(instruction, 0x4);

		EXPECT_EQ(A.out(), 0x4);
		EXPECT_EQ(B.out(), 0);
		EXPECT_EQ(IR.out(), 0);
		EXPECT_EQ(IR.address(), 0);
		EXPECT_EQ(MAR.out(), 0);
		EXPECT_EQ(PC.out(), 0);
		EXPECT_FALSE(ALU.cf());
		EXPECT_FALSE(ALU.zf());
		EXPECT_FALSE(cl->HALT);
		EXPECT_EQ(clk.remaining(), 0);
		TEST_RAM_NOT_AFFECTED();
	}

	TEST_F(ControlLogicTest, JMPShouldSetProgramCounterToAnAddressToJump)
	{
		clk.set(1);
		auto instruction = ((EmulatorLib::ControlLogic::Instruction)0b0110);
		cl->execute(instruction, 0x4);

		EXPECT_EQ(A.out(), 0);
		EXPECT_EQ(B.out(), 0);
		EXPECT_EQ(IR.out(), 0);
		EXPECT_EQ(IR.address(), 0);
		EXPECT_EQ(MAR.out(), 0);
		EXPECT_EQ(PC.out(), 0x4);
		EXPECT_FALSE(ALU.cf());
		EXPECT_FALSE(ALU.zf());
		EXPECT_FALSE(cl->HALT);
		EXPECT_EQ(clk.remaining(), 0);
		TEST_RAM_NOT_AFFECTED();
	}

	TEST_F(ControlLogicTest, JCShouldSetProgramCounterToAnAddressToJumpWhenALUOverflows)
	{
		clk.set(1);
		auto instruction = ((EmulatorLib::ControlLogic::Instruction)0b0111);
		A = 0xFF;
		B = 0x2;
		ALU.out(true);
		cl->execute(instruction, 0x4);

		EXPECT_EQ(A.out(), 0xFF);
		EXPECT_EQ(B.out(), 0x2);
		EXPECT_EQ(IR.out(), 0);
		EXPECT_EQ(IR.address(), 0);
		EXPECT_EQ(MAR.out(), 0);
		EXPECT_EQ(PC.out(), 0x4);
		EXPECT_TRUE(ALU.cf());
		EXPECT_FALSE(ALU.zf());
		EXPECT_FALSE(cl->HALT);
		EXPECT_EQ(clk.remaining(), 0);
		TEST_RAM_NOT_AFFECTED();
	}

	TEST_F(ControlLogicTest, JZShouldSetProgramCounterToAnAddressToJumpWhenALUReturnsZero)
	{
		clk.set(1);
		auto instruction = ((EmulatorLib::ControlLogic::Instruction)0b1000);
		cl->execute(instruction, 0x4);

		EXPECT_EQ(A.out(), 0x0);
		EXPECT_EQ(B.out(), 0x0);
		EXPECT_EQ(IR.out(), 0);
		EXPECT_EQ(IR.address(), 0);
		EXPECT_EQ(MAR.out(), 0);
		EXPECT_EQ(PC.out(), 0x4);
		EXPECT_FALSE(ALU.cf());
		EXPECT_FALSE(ALU.zf());
		EXPECT_FALSE(cl->HALT);
		EXPECT_EQ(clk.remaining(), 0);
		TEST_RAM_NOT_AFFECTED();
	}

	TEST_F(ControlLogicTest, OUTSouldCopyContentOfARegisterToOutRegister)
	{
		clk.set(1);
		auto instruction = ((EmulatorLib::ControlLogic::Instruction)0b1110);
		A = 0x4;
		cl->execute(instruction);

		EXPECT_EQ(A.out(), 0x4);
		EXPECT_EQ(B.out(), 0x0);
		EXPECT_EQ(OUT.out(), 0x4);
		EXPECT_EQ(IR.out(), 0);
		EXPECT_EQ(IR.address(), 0);
		EXPECT_EQ(MAR.out(), 0);
		EXPECT_EQ(PC.out(), 0x0);
		EXPECT_FALSE(ALU.cf());
		EXPECT_FALSE(ALU.zf());
		EXPECT_FALSE(cl->HALT);
		EXPECT_EQ(clk.remaining(), 0);
		TEST_RAM_NOT_AFFECTED();
	}

	TEST_F(ControlLogicTest, HALTSouldHaltTheComputer)
	{
		clk.set(1);
		auto instruction = ((EmulatorLib::ControlLogic::Instruction)0b1111);
		cl->execute(instruction);

		EXPECT_EQ(A.out(), 0);
		EXPECT_EQ(B.out(), 0);
		EXPECT_EQ(OUT.out(), 0);
		EXPECT_EQ(IR.out(), 0);
		EXPECT_EQ(IR.address(), 0);
		EXPECT_EQ(MAR.out(), 0);
		EXPECT_EQ(PC.out(), 0);
		EXPECT_FALSE(ALU.cf());
		EXPECT_FALSE(ALU.zf());
		EXPECT_TRUE(cl->HALT);
		EXPECT_EQ(clk.remaining(), 0);
		TEST_RAM_NOT_AFFECTED();
	}
}