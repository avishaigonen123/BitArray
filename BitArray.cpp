#include "BitArray.h"
#include <stdio.h>
#include <stdlib.h>

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
	m_capacity = new_capacity;

	free(tmp);
	tmp = NULL;
}