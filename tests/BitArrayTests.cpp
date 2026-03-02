#include <gtest/gtest.h>
#include "BitArray.h"
#include "Error.h"

class BitArrayTest : public testing::Test {
protected:
    BitArray bitArray;

    void SetUp() override {
        bitArray.scale(3);
        bitArray.m_storage[0] = 0x12; // 00010010
        bitArray.m_storage[1] = 0x34; // 00110100
        bitArray.m_storage[2] = 5;    // 0101
        bitArray.m_size_bits = 20;
    }

    void TearDown() override {

    }
}; 

// Test Get
TEST_F(BitArrayTest, GetTests) {
    EXPECT_EQ(bitArray.getAt(0), false);
    EXPECT_EQ(bitArray.getAt(4), true);
    EXPECT_EQ(bitArray.getAt(16), true);
    EXPECT_EQ(bitArray.getAt(17), false);
    EXPECT_EQ(bitArray.getAt(19), false);
}

TEST_F(BitArrayTest, GetOutOfBound) {
    EXPECT_EQ(bitArray.getAt(20), OutOfBound);
    EXPECT_EQ(bitArray.getAt(-1), OutOfBound);
}

// Test Set
TEST_F(BitArrayTest, SetTests) {
    bitArray.setAt(0, true);
    EXPECT_EQ(bitArray.getAt(0), true);
    bitArray.setAt(0, false);
    EXPECT_EQ(bitArray.getAt(0), false);
    bitArray.setAt(30, true);
    EXPECT_EQ(bitArray.getAt(30), true);
    bitArray.setAt(30, false);
    EXPECT_EQ(bitArray.getAt(30), false);
}

// Test to binary str
TEST_F(BitArrayTest, TestToBinary) {

}