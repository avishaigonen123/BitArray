#include "SpecialMethdos.h"
#include "stdio.h"

BitArray* SpecialMethdos::getSubArray(const BitArray& bitarray, size_t first, size_t last)  {
	// I should do it without new, but still, I'm not sure how to activate the ctor
	BitArray* res = new BitArray();
	size_t size = bitarray.getSize();
	for (size_t i = first, j=0; i <= last; i++, j++)
	{
		if (i < size)
			res->setAt(j, bitarray.getAt(i));
		else
			return res;
	}
	return res;
}

void SpecialMethdos::printHex(const BitArray& bitarray) {
	size_t size = bitarray.getSize();
	size_t res2 = 0;
	size_t i = 0;
	size_t bytes = size / 8;
	size_t bits = size % 8;
	if (bytes) {
		for (; i < size; i++) {
			res2 = res2 << 1;
			res2 += bitarray.getAt(i);
		}
		res2 = res2 << (bits);
	}
	else {
		for (; i < size; i++) {
			res2 = res2 << 1;
			res2 += bitarray.getAt(i);
		}
		res2 = res2 << (8-size);
	}
	printf("0x%x\n", res2);
	return;
}
