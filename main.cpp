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

	return 0;
}
