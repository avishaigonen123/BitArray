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

