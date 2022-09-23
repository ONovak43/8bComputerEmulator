#include "pch.h"
#include "../8bLib/ram.cpp"

namespace {
	TEST(RAMTest, RAMShouldLoadDataAtAtAnyExistingAddressAndReturnTheSameDataFromThatAddress)
	{
		EmulatorLib::RAM ram;
		ram.loadAt(0x0, 0x5);
		EXPECT_EQ(ram.dataAt(0x0), 0x5);
	}

	TEST(RAMTest, RAMShouldThrowWhenLoadingDataAtNotExistingAddress)
	{
		EmulatorLib::RAM ram;
		EXPECT_THROW(ram.loadAt(0xF, 0x5), EmulatorLib::ForbiddenActionException);
		EXPECT_THROW(ram.loadAt(0x10, 0x5), EmulatorLib::ForbiddenActionException);
	}

	TEST(RAMTest, RAMShouldThrowWhenGettingDataAtNotExistingAddress)
	{
		EmulatorLib::RAM ram;
		EXPECT_THROW(ram.dataAt(0xF), EmulatorLib::ForbiddenActionException);
		EXPECT_THROW(ram.dataAt(0x10), EmulatorLib::ForbiddenActionException);
	}

	TEST(RAMTest, RAMShouldBeFilledWithZeroesByDefault)
	{
		EmulatorLib::RAM ram;
		std::array<std::uint8_t, 15> cmp {};

		for (int i = 0; i < 15; i++) {
			ASSERT_EQ(ram.dataAt(i), cmp[i]);
		}
	}

	TEST(RAMTest, RAMShouldBeFilledWithZeroesAfterClear)
	{
		EmulatorLib::RAM ram;
		std::array<std::uint8_t, 15> cmp{};

		for (int i = 0; i < 15; i++) {
			ram.loadAt(i, 0x5);
		}

		ram.clear();

		for (int i = 0; i < 15; i++) {
			ASSERT_EQ(ram.dataAt(i), cmp[i]);
		}
	}
}