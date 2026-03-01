#include <stdio.h>
#include "BitArray.h"
#include "Error.h"

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
	BitArray* bitArray = new BitArray();
	size_t val = 0, index = 3;
	// Set up some random values at random locations
	bitArray->setAt(0, true);
	bitArray->setAt(2, true);
	bitArray->setAt(3, true);
	bitArray->setAt(4, false);

	val = bitArray->getAt(index);
	if (val > 1)
		return handle_error((Error)val);
	printf("val at index %d is %s\n", index, val ? "true" : "false");

	index = 4;
	val = bitArray->getAt(index);
	if (val > 1)
		return handle_error((Error)val);
	printf("val at index %d is %s\n", index, val ? "true" : "false");

	return 0;
}
