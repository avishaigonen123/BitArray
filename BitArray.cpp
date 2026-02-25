#include "BitArray.h"

BitArray::BitArray() {
	storage = new char[1];
	storage[0] = '\0';
	size = 0;
}

BitArray::BitArray(const BitArray& copy) {
	delete this->storage;
	this->storage = nullptr;

	this->size = copy.size;
	this->storage = new char[this->size];

	for (size_t i = 0; i < this->size; i++)
		this->storage[i] = copy.storage[i];
}

BitArray::~BitArray() {
	this->size = 0;

	delete this->storage;
	this->storage = nullptr;
}

void BitArray::SetAt(size_t index, bool value) {
	// size_t becuase i don't want negetive value (and then might have heap underflow)
	size_t bytes = index / 8;
	size_t bits = index % 8;
	if (bytes > this->size / 8 || !this->size) // if size=1, index=1, problem. if size=1, index=0, fine.
	{
		char* new_storage = new char[bytes + 1];
		size_t i = 0;

		for (; i <= this->size / 8; i++)
		{
			new_storage[i] = this->storage[i];
		}
		for (; i <= bytes; i++)
		{
			new_storage[i] = '\0';
		}
		delete this->storage;
		this->storage = new_storage;
	}
	if (index > this->size)
		this->size = index+1;
	if (value) // value is 1
		this->storage[bytes] |= bits ? (1 << bits) : 1; // OR with 00010000 (index)1
	else
		this->storage[bytes] &= bits ? (~(1 << bits)) : !1; // AND with 11101111 (index)

}

bool BitArray::GetAt(size_t index) const {
	// function is const becuase i don't want to change to values of the fields at "this", the class.
	size_t bytes = index / 8;
	size_t bits = index % 8;
	return (this->storage[bytes] >> bits) & 1; // take the right bytes, shift right, and mask with 1 (to get the exact bit)
}

bool BitArray::ToBinaryStr(char* o_binaryStr, size_t binaryStrSize) const {
	if (binaryStrSize < this->size) // maybe need to adjust this
		return 1;

	o_binaryStr = new char[binaryStrSize + 1]; // the size already include the null (that's what I understood)
	char* ptr = o_binaryStr;
	char loc;
	char opt[2] = { '0','1' };
	for (size_t i = 0; i < binaryStrSize; i++) {
		loc = this->storage[i];
		for (int j = 7; j >= 0; j--)
		{
			*ptr = opt[(loc >> j) & 1];
			ptr++;
		}
	}
	ptr = '\0';

	return 0;
}

bool BitArray::FromBinaryStr(const char* i_binaryStr, size_t binaryStrLen) {
	int bit_size = binaryStrLen * 8;
	if (binaryStrLen > this->size)
		return 1;
	// I guess I don't need to adjust the size according to the input from the binary str

	const char* ptr = i_binaryStr;
	char loc;
	for (size_t i = 0; i < binaryStrLen; i++)
	{
		loc = '\0';
		for (int j = 7; j >= 0; j--)
		{
			loc += (*ptr) - '0'; // 0 or 1
			1 << loc;
			ptr++;
		}
		this->storage[i] = loc;
	}

	return 0;
}


