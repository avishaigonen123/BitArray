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
	BitArray *bitarray = new BitArray();
	for (int i = 0; i < 20; i++)
	{
		bitarray->SetAt(i, 0);
		printf("%d", bitarray->GetAt(i));
	}
	printf("\n");

	for (int i = 0; i < 10; i++)
	{
		bitarray->SetAt(i, 1);
		printf("%d", bitarray->GetAt(i));
	}
	printf("\n");
	//bitarray->SetAt(5, 1);
	bitarray->SetAt(5, 0);
	//bitarray->SetAt(16, 1);
	for (int i = 0; i < 34; i++)
	{
		printf("%d", bitarray->GetAt(i));
	}
	printf("\n");
	return 0;
}