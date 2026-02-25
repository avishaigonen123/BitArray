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
	delete[] this->storage;
	this->storage = nullptr;
}

size_t BitArray::getSize() const
{
	return this->size;
}

void BitArray::resize(size_t new_capacity) {
	if (new_capacity < capacity) // resizing can't work
		return;

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
	capacity = new_capacity;

	delete[]tmp;
	tmp = nullptr;
}

// - Answer: size_t becuase i don't want negetive value (and then might have heap underflow)
void BitArray::SetAt(size_t index, bool value) {
	size_t bytes = index / 8;
	size_t bits = index % 8;

	if (this->capacity * 8 < index) // we need more capacity
		resize(bytes + 1);
	if (this->size < index) // enlarge the size
		this->size = index;

	if (value) 
		this->storage[bytes] = this->storage[bytes] | (bits ? (1 << bits) : 1); // OR 00010000
	else
		this->storage[bytes] = this->storage[bytes] & (bits ? ~(1 << bits) : 0xfe);// AND 11101111
}

// - Answer: function is const becuase i don't want to change to values of the fields at "this", the class.
size_t BitArray::GetAt(size_t index) const {
	if (index > size)
		return OutOfBound;
	
	size_t bytes = index / 8;
	size_t bits = index % 8;

	return (this->storage[bytes] >> (bits)) & 1; // take the right byte, shift right, and mask with 1 (to get the exact bit)
}

size_t BitArray::ToBinaryStr(char* o_binaryStr, size_t binaryStrSize) const {
	if (binaryStrSize > this->size) // bigger than the size
		return HeapOverflow;

	char* ptr = o_binaryStr; // we'll move and add the characters. I assume a place had already been allocated at o_binaryStr
	size_t* ptr_storage = this->storage;
	size_t curr, i = 0;
	while(i < binaryStrSize) {
		curr = *ptr_storage;
		for (int j = 0; j < 8 && i < binaryStrSize; i++, j++)
		{
			*ptr = ((curr >> j) & 1) ? '1' : '0';
+			ptr++;
		}
		ptr_storage++;
	}
	*ptr = '\0';

	return 0;
}

size_t BitArray::FromBinaryStr(const char* i_binaryStr, size_t binaryStrLen) {
	if (binaryStrLen > this->size) // I assume binaryStrLen is without NULL
		this->SetAt(binaryStrLen, false); // we'll call resize with the right capacity

	this->size = binaryStrLen;

	// Check for binary values
	for (int i = 0; i < binaryStrLen; i++)
		if (i_binaryStr[i] != '0' && i_binaryStr[i] != '1')
			return NotBinaryValue;

	const char* ptr = i_binaryStr;
	size_t* ptr_storage = this->storage;
	size_t loc = '\0', i = 0;
	size_t bytes = binaryStrLen / 8;
	size_t bits = binaryStrLen % 8;

	for (size_t i = 0; i < bytes; i++)
	{
		for (int j = 7; j >= 0; j--)
		{
			loc = loc << 1; // built the number, shift left by 1
			if (ptr[8*i + j] - '0') // this is '1'
				loc |= 1;
			else            // this is '0'
				loc &= ~1;
		}
		*ptr_storage = loc;
		ptr_storage++;
		loc = '\0';
	}
	if (bits) {
		for (int j = bits-1; j >= 0; j--)
		{
			loc = loc << 1; // built the number, shift left by 1
			if (ptr[8 * bytes + j] - '0') // this is '1'
				loc |= 1;
			else            // this is '0'
				loc &= ~1;
		}
		*ptr_storage = loc;
	}
	return 0;
}

bool BitArray::operator[](size_t index) const {
	return this->GetAt(index);
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

