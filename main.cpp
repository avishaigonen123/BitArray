#include <stdio.h>
#include "BitArray.h"
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
			break;
		case HeapUnderflow:
			break;
		case SizeNotMatch:
			break;
		default:
			printf("Unknown error\n");
			break;
	}

	return -1;
}

int main() {
	BitArray* bitArray = new BitArray();
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

	return 0;
}