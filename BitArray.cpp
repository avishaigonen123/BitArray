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
		this->storage[bytes] = this->storage[bytes] & (bits ? ~(1 << bits) : 0xff);// AND 11101111
}

// - Answer: function is const becuase i don't want to change to values of the fields at "this", the class.
size_t BitArray::GetAt(size_t index) const {
	if (index > size)
		return OutOfBound;
	
	size_t bytes = index / 8;
	size_t bits = index % 8;

	return (this->storage[bytes] >> (bits)) & 1; // take the right byte, shift right, and mask with 1 (to get the exact bit)
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


