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
	free(this->m_storage);
	this->m_storage = NULL;
}

size_t BitArray::getSize() const {
	return this->m_size_bits;
}

void BitArray::scale(size_t new_capacity) {
	// we can also simply use realloc, not forget to free the memory of the first parameter if realloc fails.
	//size_t* tmp = (size_t*)realloc(this->m_storage, new_capacity * sizeof(size_t));

	// Becuase I've already implemented this resize, I'll leave it as is.
	// In realloc there is also functionly for shrinking the size, I don't have it becuase the resize is internal helper function, and I don't need shrinking.
	size_t* tmp = this->m_storage;
	size_t i = 0;

	if (new_capacity < m_capacity_bytes) // only scaling, not shrinking
		return;

	// I want to reset with zero values, all blocks
	this->m_storage = (size_t*)calloc(new_capacity, sizeof(size_t));
	if (!this->m_storage) {
		printf("Error memory allocation\n");
		return;
	}
	// copy bytes for old storage, new bytes will be already 0
	for (; i < m_capacity_bytes; i++) {
		if (!tmp)
			this->m_storage[i] = NULL;
		else
			this->m_storage[i] = tmp[i];
	}
	// set new capacity
	this->m_capacity_bytes = new_capacity;
}

// - Answer: size_t becuase i don't want negetive value (and then might have heap underflow)
void BitArray::setAt(size_t index, bool value) {
	size_t bytes = index / 8;
	size_t bits = index % 8;
	
	if (this->m_capacity_bytes * 8 < index) // we need more capacity, one above the desired bytes
		scale(bytes + 1);
	if (this->m_size_bits < index) // enlarge the size
		this->m_size_bits = index;

	if (value) 
		this->m_storage[bytes] = this->m_storage[bytes] | (bits ? (1 << bits) : 1); // OR 00010000
	else
		this->m_storage[bytes] = this->m_storage[bytes] & (bits ? ~(1 << bits) : 0xff);// AND 11101111
}

// - Answer: function is const becuase i don't want to change to values of the fields at "this", the class.
size_t BitArray::getAt(size_t index) const {
	size_t bytes = index / 8;
	size_t bits = index % 8;

	// trying to get out of bound value
	if (index > m_size_bits)
		return OutOfBound;

	// take the correct byte, shift right, and mask with 1 (to get the exact bit)
	return (this->m_storage[bytes] >> (bits)) & 1; 
}
