# include "BitArray.h"
#include "stdio.h"
#include "Error.h"

#define CHECK_AND_PRINT(format, expr, index)             \
    do {                                                 \
        int val = (expr);                                \
        if (val > 1)                                     \
            return handle_error((Error)val);             \
        printf(format, index, val);\
    } while(0)

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
	
	index = 3;
	CHECK_AND_PRINT("val at index %d is %d\n", bitArray->GetAt(index), index);

	bool value = true;
	printf("Set value at index %d to %d\n", index, value);
	bitArray->SetAt(index, value);
	
	CHECK_AND_PRINT("value at index %d is: %d\n", bitArray->GetAt(index), index);
	CHECK_AND_PRINT("value at index %d is: %d\n", (*bitArray)[index], index);


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
	CHECK_AND_PRINT("value at index %d is: %d\n", bitArray->GetAt(index), index);

	val = bitArray->compare(copy);
	if (val > 1)
		return handle_error((Error)val);
	printf("comparing check result: %s\n", val ? "false" : "true");
	copy.SetAt(2, true);
	bitArray->SetAt(2, false);
	val = bitArray->compare(copy);
	if (val > 1)
		return handle_error((Error)val);
	printf("comparing check result: %s\n", val ? "false" : "true");
	index = 2;
	CHECK_AND_PRINT("value at index %d for bitArray is: %d\n", bitArray->GetAt(index), index);
	CHECK_AND_PRINT("value at index %d for copy is: %d\n", copy.GetAt(index), index);

	return 0;
}

