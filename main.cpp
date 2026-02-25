#include <stdio.h>
#include <stdlib.h>
#include "BitArray.h"
#include "Error.h"

// Macro chatGPT created for me in order to save time when calling to functions like setAt, getAt and operator[]
#define CHECK_AND_PRINT(format, expr, index)             \
    do {                                                 \
        int val = (expr);                                \
        if (val > 1)                                     \
            return handle_error((Error)val);             \
        printf(format, index, val);\
    } while(0)

/**
 * @brief function that handles errors by given error status code, prints message and return fail or success to the caller
 * @param err the status code that being given
 * @return 0 if success, -1 if fails
*/
int handle_error(Error err) {
	switch (err) {	
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
			printf("Sizes not match\n");
			break;
		default:
			printf("Unknown error\n");
			break;
	}

	return -1;
}

int main() {
	// but now, How do I call the ctor? 
	//BitArray* bitArray = (BitArray*)malloc(sizeof(BitArray));
	BitArray* bitArray = new BitArray();
	size_t val = 0, index = 0;
	bool value = false;
	const char* const_binary_string = "1001000110";
	char* binary_string = NULL;
	BitArray *copy = NULL;

	// test set and get
	bitArray->setAt(0, true);
	bitArray->setAt(2, true);
	bitArray->setAt(3, true);
	bitArray->setAt(4, false);
	
	val = bitArray->getAt(index);
	index = 3;
	CHECK_AND_PRINT("val at index %d is %d\n", bitArray->getAt(index), index);

    value = true;
	printf("Set value at index %d to %d\n", index, value);
	bitArray->setAt(index, value);
	CHECK_AND_PRINT("value at index %d is: %d\n", bitArray->getAt(index), index);

	// test toBinary and fromBinary
	bitArray->fromBinaryStr(const_binary_string, 10);
	binary_string = (char*)malloc(11 * sizeof(char));
	val = bitArray->toBinaryStr(binary_string, 10);
	if (val > 1)
		return handle_error((Error)val);
	printf("string is %s\n", binary_string);
	free(binary_string);

	// test compare
	copy = new BitArray(*bitArray);
	CHECK_AND_PRINT("value at index %d is: %d\n", bitArray->getAt(index), index);

	val = bitArray->compare(*copy);
	if (val > 1)
		return handle_error((Error)val);
	printf("comparing check result: %s\n", val ? "false" : "true");
	index = 2;
	copy->setAt(index, true);
	CHECK_AND_PRINT("bitArray1: value at index %d is: %d\n", bitArray->getAt(index), index);
	bitArray->setAt(index, false);
	CHECK_AND_PRINT("bitArray2: value at index %d is: %d\n", bitArray->getAt(index), index);
	val = bitArray->compare(*copy);
	if (val > 1)
		return handle_error((Error)val);
	printf("comparing check result: %s\n", val ? "false" : "true");

	return 0;
}
