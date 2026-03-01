#include <stdio.h>
#include <stdlib.h>
#include "BitArray.h"
#include "Error.h"

BitArray::BitArray() {
	m_capacity_bytes = 0;
	m_size_bits = 0;
	m_storage = NULL;
	// scale the storage to 1 byte capacity
	scale(1); 
}

BitArray::BitArray(const BitArray& copy) {
	free(m_storage);
	this->m_storage = NULL;

	this->m_size_bits = copy.m_size_bits;
	this->m_capacity_bytes = copy.m_capacity_bytes;
	this->m_storage = (size_t*)malloc(this->m_capacity_bytes * sizeof(size_t));
	if (!this->m_storage) {
		printf("Error memory allocation\n");
		return;
	}
	// deep copy each byte block
	for (size_t i = 0; i < this->m_capacity_bytes; i++)
		this->m_storage[i] = copy.m_storage[i];
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
		this->storage[bytes] |= (1 << bits); // OR with 00010000 (index)1
	else
		this->storage[bytes] &= (~(1 << bits)); // AND with 11101111 (index)

}

bool BitArray::GetAt(size_t index) const {
	// function is const becuase i don't want to change to values of the fields at "this", the class.
	size_t bytes = index / 8;
	size_t bits = index % 8;
	return (this->storage[bytes] >> bits) & 1; // take the right bytes, shift right, and mask with 1 (to get the exact bit)
}

bool BitArray::ToBinaryStr(char* o_binaryStr, size_t binaryStrSize) const {
	if (binaryStrSize > this->size) // maybe need to adjust this
		return 1;

	char* ptr = o_binaryStr;
	char* ptr_storage = this->storage;
	char loc;
	char opt[2] = { '0','1' };
	for (int i = binaryStrSize; i > 0;) {
		loc = *ptr_storage;
		for (int j = 7; j >= 0 && i > 0; i--, j--)
		{
			*ptr = opt[(loc >> j) & 1];
+			ptr++;
		}
		ptr_storage++;
	}
	*ptr = '\0';

	return 0;
}

bool BitArray::FromBinaryStr(const char* i_binaryStr, size_t binaryStrLen) {
	if (binaryStrLen > this->size) // I assume binaryStrLen is without NULL
	{
		this->size = binaryStrLen;
		delete this->storage;
		this->storage = new char[binaryStrLen+1];
	}

	const char* ptr = i_binaryStr;
	char* ptr_storage = this->storage;
	char loc;
	for (int i = binaryStrLen; i > 0;) {
		loc = '\0';
		for (int j = 0; j < 8 && i > 0; i--, j++)
		{
			loc = loc << 1; // built the number, shift right by 1
			if (*ptr - '0' == 0) // this is '0'
				loc &= ~1;
			else
				loc |= 1;
			ptr++;
		}
		*ptr_storage = loc;
		ptr_storage++;
	}


	return 0;
}


