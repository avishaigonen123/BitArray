#include "BitArray.h"
#include "Error.h"

BitArray::BitArray() {
	capacity = 0;
	size = 0;
	storage = nullptr;
	resize(1);
}

BitArray::BitArray(const BitArray& copy) {
	delete[] this->storage;
	this->storage = nullptr;

	this->size = copy.size;
	this->capacity = copy.capacity;
	this->storage = new size_t[this->capacity];

	for (size_t i = 0; i < this->capacity; i++)
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
	char mask = !((bits << 1) & this->storage[bytes]); // I want mask, like 11101111

	this->storage[bytes] = (this->storage[bytes] & mask) + (bits << 1); // turn of the bit with inx, and add it after left shift. 
}

bool BitArray::GetAt(size_t index) const {
	// function is const becuase i don't want to change to values of the fields at "this", the class.
	size_t bytes = index / 8;
	size_t bits = index % 8;
	return (this->storage[bytes] >> (bits - 1)) & 1; // take the right bytes, shift right, and mask with 1 (to get the exact bit)
}

