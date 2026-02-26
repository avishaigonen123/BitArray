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

	index = 4, val = bitArray->GetAt(index);
	if (val > 1)
		return handle_error((Error)val);
	printf("val at index %d is %s\n", index, val ? "true" : "false");

	// test ToBinary and FromBinary
	const char* a = "1001000110";
	char* b;
	bitArray->FromBinaryStr(a, 10);
	b = new char[11];
	val = bitArray->ToBinaryStr(b,10);
	if (val > 1)
		return handle_error((Error)val);
	printf("string is %s\n", b);

	return 0;
}