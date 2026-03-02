#include <stdio.h>
#include <stdlib.h>
#include "BitArray.h"
#include "Error.h"
# define BYTE 8

BitArray::BitArray() {
	m_size_bits = 0;
	m_capacity_bytes = 1;
	m_storage = (size_t*)calloc(m_capacity_bytes, BYTE);
	if (!m_storage)
		m_capacity_bytes = 0;
}

BitArray::BitArray(const BitArray& copy) {
	free(m_storage);
	this->m_storage = NULL;

	this->m_size_bits = copy.m_size_bits;
	this->m_capacity_bytes = copy.m_capacity_bytes;
	this->m_storage = (size_t*)malloc(this->m_capacity_bytes * sizeof(size_t));
	if (!this->m_storage) {
		printf("Error memory allocation\n");
		this->m_size_bits = 0;
		this->m_capacity_bytes = 0;
		return;
	}

	for (size_t i = 0; i < this->m_capacity_bytes; i++) {
		this->m_storage[i] = copy.m_storage[i];
	}
}

BitArray::~BitArray() {
	free(this->m_storage);
	this->m_storage = NULL;
}

size_t BitArray::getSize() const {
	return this->m_size_bits;
}

size_t BitArray::getCapacity() const {
	return this->m_capacity_bytes;
}

void BitArray::scale(size_t new_capacity) {
	size_t* new_storage = NULL;
	size_t inx = 0;

	// only scaling, not shrinking
	if (new_capacity < m_capacity_bytes) {
		return;
	}

	this->m_storage = (size_t*)calloc(new_capacity, sizeof(size_t));
	if (!this->m_storage) {
		this->m_size_bits = 0;
		this->m_capacity_bytes = 0;
		printf("Error memory allocation\n");
		return;
	}

	new_storage = new size_t[new_capacity];
	for (; inx < m_capacity_bytes; inx++) {
		new_storage[inx] = this->m_storage[inx];
	}
	// set new capacity
	this->m_capacity_bytes = new_capacity;

	free(this->m_storage);
	this->m_storage = new_storage;
}

// - Answer: size_t becuase i don't want negetive value (and then might have heap underflow)
void BitArray::setAt(size_t index, bool value) {
	size_t bytes = index / BYTE;
	size_t bits = index % BYTE;	

	// we need more capacity, one above the desired bytes
	if (this->m_capacity_bytes * BYTE < index) {
		scale(bytes + 1);
		if (this->m_capacity_bytes == 0) {
			printf("scale fails\n");
			return;
		}
	}
	if (this->m_size_bits <= index) {
		this->m_size_bits = index;
	}
	if (value) {
		this->m_storage[bytes] = this->m_storage[bytes] | (bits ? (1 << bits) : 1); // OR 00010000
	}
	else {
		this->m_storage[bytes] = this->m_storage[bytes] & (bits ? ~(1 << bits) : 0xff); // AND 11101111
	}
}

// - Answer: function is const becuase i don't want to change to values of the fields at "this", the class.
size_t BitArray::getAt(size_t index) const {
	size_t bytes = index / BYTE;
	size_t bits = index % BYTE;

	if (index > m_size_bits) {
		return OutOfBound;
	}

	// take the correct byte, shift right, and mask with 1 (to get the exact bit)
	return (this->m_storage[bytes] >> (bits)) & 1;
}

size_t BitArray::toBinaryStr(char* o_binaryStr, size_t binaryStrSize) const {
	char* ptr = o_binaryStr;
	char* ptr_storage = this->m_storage;
	size_t current = 0, i = 0;

	// bigger than the size	
	if (binaryStrSize > this->m_size_bits) {
		return HeapOverflow;
	}

	// we'll move and add the characters. I assume a place had already been allocated at o_binaryStr
	while (i < binaryStrSize) {
		current = *ptr_storage;
		for (int j = 0; j < BYTE && i < binaryStrSize; i++, j++) {
			*ptr = ((current >> j) & 1) ? '1' : '0';
			ptr++;
		}
		ptr_storage++;
	}
	// add NULL at the end of the string
	*ptr = NULL;

	return 0;
}

/**
 * @brief helper method for converting from bytes to str
 * @param num_of_bytes number of bytes in string
 * @param i_binaryStr the string that holds the values
 * @param m_storage the storage will put the values inside
*/
void from_bytes_to_str(size_t num_of_bytes, const char* i_binaryStr, size_t* m_storage) {
	size_t* ptr_storage = m_storage;
	size_t current = 0;

	for (size_t i = 0; i < num_of_bytes; i++) {
		for (int j = 7; j >= 0; j--) {
			current = current << 1; // built the number, shift left by 1
			if (i_binaryStr[BYTE * i + j] - '0') { // this is '1'
				current |= 1;
			}
			else {                    // this is '0'
				current &= ~1;
			}
		}
		*ptr_storage = current;
		ptr_storage++;
		current = 0;
	}
}

/**
 * @brief helper method for converting from bits to str
 * @param num_of_bytes number of bytes in string
 * @param num_of_bits number of bits in string
 * @param i_binaryStr the string that holds the values
 * @param m_storage the storage will put the values inside
*/
void from_bits_to_str(size_t num_of_bytes, size_t num_of_bits, const char * i_binaryStr, size_t* m_storage) {
	size_t current = 0;

	for (int j = num_of_bits - 1; j >= 0; j--) {
		current = current << 1; // built the number, shift left by 1
		if (i_binaryStr[BYTE * num_of_bytes + j] - '0') { // this is '1'
			current |= 1;
		}
		else {            // this is '0'
			current &= ~1;
		}
	}
	m_storage[num_of_bytes + 1] = current;
}

size_t BitArray::fromBinaryStr(const char* i_binaryStr, size_t binaryStrLen) {
	size_t num_of_bytes = binaryStrLen / BYTE;
	size_t num_of_bits = binaryStrLen % BYTE;
	size_t current = 0, i = 0;

	if (binaryStrLen > this->m_size_bits) {
		this->scale(num_of_bytes);
	}

	this->m_size_bits = binaryStrLen;

	// Check for binary values
	for (size_t i = 0; i < binaryStrLen; i++) {
		if (i_binaryStr[i] != '0' && i_binaryStr[i] != '1') {
			return NotBinaryValue;
		}
	}
	from_bytes_to_str(num_of_bytes, i_binaryStr, this->m_storage);
	
	// There are more several bits which aren't full byte
	if (num_of_bits) {
		from_bits_to_str(num_of_bytes, num_of_bits, i_binaryStr, this->m_storage);
	}

	return 0;
}

size_t BitArray::operator[](size_t index) const {
	return this->getAt(index);
}

size_t BitArray::compare(const BitArray& other) const{
	int i = this->m_size_bits;
	int j = 0;

	// bit sizes not match, compare failess
	if (this->m_size_bits != other.m_size_bits) {
		return 1;
	}

	// check for each byte
	while (i > 7) {
		if (this->m_storage[j] - other.m_storage[j] != 0) {
			return 1;
		}
		i -= BYTE;
		j++;
	}
	// check for the remains bit
	if (i) { 
		for (i = this->m_size_bits % BYTE; i > 0; i--) {
			if ((this->m_storage[j] >> i) - (other.m_storage[j] >> i) != 0) {
				return 1;
			}
		}
	}

	return 0;
}
