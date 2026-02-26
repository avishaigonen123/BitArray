#include "BitArray.h"

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
	delete[] this->storage;
	this->storage = nullptr;
}

size_t BitArray::getSize() const
{
	return this->size;
}

void BitArray::resize(size_t new_capacity) {
	size_t* tmp;
	tmp = this->storage;

	this->storage = new size_t[new_capacity];
	size_t i;
	for (i = 0; i < capacity; i++)
	{
		this->storage[i] = tmp[i];
	}
	for (; i < new_capacity; i++)
	{
		this->storage[i] = '\0';
	}

	delete[]tmp;
	tmp = nullptr;
}

