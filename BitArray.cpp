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

