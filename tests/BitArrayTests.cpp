#include <gtest/gtest.h>
#include "BitArray.h"
#include "Error.h"

class BitArrayTest : public testing::Test {
protected:
    BitArray bit_array;
    char* binary_str;
    size_t size_binary_str;
    const char* const_binary_str = "001001001001001";
    const size_t const_size_binary_str = 16;

    void SetUp() override {
        bit_array.scale(3);
        bit_array.m_storage[0] = 0x12; // 00010010
        bit_array.m_storage[1] = 0x34; // 00110100
        bit_array.m_storage[2] = 5;    // 0101
        bit_array.m_size_bits = 20;

        size_binary_str = 30;
        binary_str = (char*)malloc(size_binary_str * sizeof(char));
    }

    void TearDown() override {
        free(binary_str);
        binary_str = NULL;
    }
}; 

// Test Get
TEST_F(BitArrayTest, GetTests) {
    EXPECT_EQ(bit_array.getAt(0), false);
    EXPECT_EQ(bit_array.getAt(4), true);
    EXPECT_EQ(bit_array.getAt(16), true);
    EXPECT_EQ(bit_array.getAt(17), false);
    EXPECT_EQ(bit_array.getAt(19), false);
}

TEST_F(BitArrayTest, GetOutOfBound) {
    EXPECT_EQ(bit_array.getAt(20), OutOfBound);
    EXPECT_EQ(bit_array.getAt(-1), OutOfBound);
}

// Test Set
TEST_F(BitArrayTest, SetTests) {
    bit_array.setAt(0, true);
    EXPECT_EQ(bit_array.getAt(0), true);
    bit_array.setAt(0, false);
    EXPECT_EQ(bit_array.getAt(0), false);
    bit_array.setAt(30, true);
    EXPECT_EQ(bit_array.getAt(30), true);
    bit_array.setAt(30, false);
    EXPECT_EQ(bit_array.getAt(30), false);
}

// Test to binary str
TEST_F(BitArrayTest, ToBinary) {

}

TEST_F(BitArrayTest, ToBinaryHeapOverflow) {
    EXPECT_EQ(bit_array.toBinaryStr(binary_str, bit_array.getSize()), 0);
    EXPECT_EQ(bit_array.toBinaryStr(binary_str, bit_array.getSize() + 1), HeapOverflow);
    EXPECT_EQ(bit_array.toBinaryStr(binary_str, -1), HeapOverflow);
}


