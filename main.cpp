# include "BitArray.h"
#include "stdio.h"
#include "Error.h"

int handle_error(Error err) {
	switch (err)
	{	
		case Success:
			printf("success\n");
			return 0;
			break;
		case OutOfBound:
			printf("Out of bound\n");
			break;
		case HeapOverflow:
			printf("Heap overflow\n");
			break;
		case HeapUnderflow:
			printf("Heap underflow\n");
			break;
		case SizeNotMatch:
			printf("Size not match\n");
			break;
		default:
			printf("Unknown error\n");
			break;
	}

	return -1;
}

int main() {
	BitArray* bitArray = new BitArray();
	// test set and get
	size_t val, index;
	bitArray->SetAt(0, true);
	bitArray->SetAt(2, true);
	bitArray->SetAt(3, true);
	bitArray->SetAt(4, false);
	
	index = 3, val = bitArray->GetAt(index);
	if (val > 1)
		return handle_error((Error)val);
	printf("val at index %d is %s\n", index, val ? "true" : "false");

	bool value = true;
	printf("Set value at index %d to %d\n", index, value);
	bitArray->SetAt(index, value);
	printf("value at index %d is: %d\n", index, bitArray->GetAt(index));
	printf("value at index %d is: %d\n", index, (*bitArray)[index]);


	// test ToBinary and FromBinary
	const char* a = "1001000110";
	char* b;
	bitArray->FromBinaryStr(a, 10);
	b = new char[11];
	val = bitArray->ToBinaryStr(b, 10);
	if (val > 1)
		return handle_error((Error)val);
	printf("string is %s\n", b);

	// test compare feature
	BitArray copy = BitArray(*bitArray);
	printf("comparing check result at %d\n", bitArray->compare(copy));
	copy.SetAt(2, false);
	printf("comparing check result at %d\n", bitArray->compare(copy));
	index = 4, val = bitArray->GetAt(index);
	if (val > 1)
		return handle_error((Error)val);
	printf("val at index %d is %s\n", index, val ? "true" : "false");

	

	return 0;
}

