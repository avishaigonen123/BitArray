#include "SpecialMethdos.h"
#include "stdio.h"

BitArray* SpecialMethdos::GetSubArray(BitArray& bitarray, size_t first, size_t last)  {
	BitArray* res = new BitArray();
	for (size_t i = first, j=0; i <= last; i++, j++)
	{
		res->SetAt(j, bitarray.GetAt(i));
	}
	return res;
}

void SpecialMethdos::PrintHex(BitArray& bitarray) {
	size_t size = bitarray.GetSize();
	int res2 = 0;
	int j = 0;
	int bytes = 0;
	int bits = 0;
	for (int i = 0; i < size; i++)
	{
		res2 = res2 << 1;
		j = bitarray.GetAt(bytes + bits--);
		res2 += j;
		if ((i + 1) % 8) {
			bytes += 8;
			bits = 7;
		}
	}
	res2 = res2 << (size % 4);
	printf("0x%x\n", res2);
	return;
	char* res = new char[size+1];
	char* ptr = res;
	int inx = 3;
	size_t i;
	*ptr = '\0';
	printf("0x");
	for (i = 0; i < size; i++)
	{
		*ptr = *ptr << 1;
		*ptr += bitarray.GetAt((int)i + inx);
		inx -= 2;
		if ((!((i + 1) % 4)) ) // divisible by 4
		{
			printf("%01x", *ptr);
			ptr++;
			*ptr = '\n';
			inx = 3;
		}
	}
	printf("\n");
	*ptr = *ptr << (size % 4);

	//printf("hex value: 0x%x\n");
	delete[] res;
	res = nullptr;
}

