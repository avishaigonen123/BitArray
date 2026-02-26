#include "SpecialMethdos.h"

BitArray* SpecialMethdos::GetSubArray(BitArray& bitarray, size_t first, size_t last)  {
	BitArray* res = new BitArray();
	for (size_t i = first; i < last; i++)
	{
		res->SetAt(i, bitarray.GetAt(i));
	}
	return res;
}

void SpecialMethdos::PrintHex(BitArray& bitarray) {
	
}

