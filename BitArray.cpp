#include <stdio.h>
#include <stdlib.h>
#include "BitArray.h"
#include "Error.h"

BitArray::BitArray() {
	m_capacity = 0;
	m_size = 0;
	m_storage = NULL;
	resize(1);
}

BitArray::BitArray(const BitArray& copy) {
	free(m_storage);
	this->m_storage = NULL;

	this->m_size = copy.m_size;
	this->m_capacity = copy.m_capacity;
	this->m_storage = new size_t[this->m_capacity];
	this->m_storage = (size_t*)malloc(this->m_capacity * sizeof(size_t));
	if (!this->m_storage) {
		printf("Error memory allocation\n");
		return;
	}
	for (size_t i = 0; i < this->m_capacity; i++)
		this->m_storage[i] = copy.m_storage[i];
}

BitArray::~BitArray() {
	free(this->m_storage);
	this->m_storage = NULL;
}

size_t BitArray::getSize() const
{
	return this->m_size;
}

void BitArray::resize(size_t new_capacity) {
	// we can also simply use realloc, not forget to free the memory of the first parameter if realloc fails.
	//size_t* tmp = (size_t*)realloc(this->m_storage, new_capacity * sizeof(size_t));

	// Becuase I've already implemented this resize, I'll leave it as is.
	// In realloc there is also functionly for shrinking the size, I don't have it becuase the resize is internal helper function, and I don't need shrinking.

	size_t* tmp = this->m_storage;
	size_t i = 0;

	if (new_capacity < m_capacity) // resizing can't work
		return;

	this->m_storage = (size_t*)calloc(new_capacity, sizeof(size_t));
	if (!this->m_storage) {
		printf("Error memory allocation\n");
		return;
	}
	for (; i < m_capacity; i++)
	{
		if (!tmp)
			this->m_storage[i] = NULL;
		else
			this->m_storage[i] = tmp[i];
	}
	
	this->m_capacity = new_capacity;
}

// - Answer: size_t becuase i don't want negetive value (and then might have heap underflow)
void BitArray::SetAt(size_t index, bool value) {
	size_t bytes = index / 8;
	size_t bits = index % 8;
	
	if (this->m_capacity * 8 < index) // we need more capacity
		resize(bytes + 1);
	if (this->m_size < index) // enlarge the size
		this->m_size = index;

	if (value) 
		this->m_storage[bytes] = this->m_storage[bytes] | (bits ? (1 << bits) : 1); // OR 00010000
	else
		this->m_storage[bytes] = this->m_storage[bytes] & (bits ? ~(1 << bits) : 0xff);// AND 11101111
}

// - Answer: function is const becuase i don't want to change to values of the fields at "this", the class.
size_t BitArray::GetAt(size_t index) const {
	size_t bytes = index / 8;
	size_t bits = index % 8;

	if (index > m_size)
		return OutOfBound;

	return (this->m_storage[bytes] >> (bits)) & 1; // take the right byte, shift right, and mask with 1 (to get the exact bit)
}
