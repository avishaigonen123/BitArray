#include "SpecialMethdos.h"
#include "stdio.h"

BitArray* SpecialMethdos::getSubArray(const BitArray* const bitarray, size_t first_index, size_t last_index)  {
	BitArray* sub_array = new BitArray();
	size_t size = bitarray->getSize();
	size_t capacity = 0;
	if (first_index > size || last_index > size) {
		return sub_array;
	}
	capacity = ((last_index - first_index) / sizeof(size_t));
	sub_array->scale(capacity);
	for (size_t i = first_index; i <= last_index; i++)
	{
		sub_array->setAt(i - first_index, bitarray->getAt(i));
	}

	return sub_array;
}

void SpecialMethdos::printHex(const BitArray& bitarray) {
	size_t size = bitarray.getSize();
	size_t number_to_print = 0;
	size_t bytes = size / sizeof(size_t);
	size_t bits = size % sizeof(size_t);
	if (bytes) {
		for (size_t i = 0; i < size; i++) {
			number_to_print = number_to_print << 1;
			number_to_print += bitarray.getAt(i);
		}
		number_to_print = number_to_print << (4 - (bits % 4));
	}
	else {
		for (size_t i = 0; i < size; i++) {
			number_to_print = number_to_print << 1;
			number_to_print += bitarray.getAt(i);
		}
		number_to_print = number_to_print << (sizeof(size_t)-size);
	}
	printf("0x%x\n", number_to_print);
	return;
}
