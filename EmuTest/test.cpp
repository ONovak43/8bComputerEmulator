#include "pch.h"
#include "../8bComputerEmulator/alu.h"
#include "../8bComputerEmulator/register.h"

/*class ALUTest : public ::testing::Test
{
protected:
	ALUTest() : alu{ A, B } {};
	void SetUp() override
	{
		//A.Value(5);
		//B.Value(4);
	}

	EmulatorLib::ALU alu;
	EmulatorLib::Register A;
	EmulatorLib::Register B;
};*/

TEST(ALUTest, TestName) {
	EmulatorLib::Register A;
	EmulatorLib::Register B;
	EmulatorLib::ALU alu(A, B);
	//EXPECT_EQ(alu.Value(), 1);
}