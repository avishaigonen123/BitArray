#include <stdio.h>
#include <stdlib.h>
#include "BitArray.h"
#include "Error.h"
#include "SpecialMethdos.h"

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
			printf("Unknown error, error status code is %d\n", err);
			break;
	}

	return -1;
}

/**
 * @brief function that tests the getBy and setBy functionality, return 0 if succeed
 * @param bitArray the instance of the BitArray to work on
 * @return 0 if true, otherwise, it'll return value different then 0
*/
int test_set_get(BitArray* bitArray) {
	bool value = false;
	size_t index = 0;

	bitArray->setAt(0, true);
	bitArray->setAt(2, true);
	bitArray->setAt(3, true);
	bitArray->setAt(4, false);

	index = 3;
	CHECK_AND_PRINT("val at index %d is %d\n", bitArray->getAt(index), index);

	value = true;
	printf("Set value at index %d to %d\n", index, value);
	bitArray->setAt(index, value);
	CHECK_AND_PRINT("value at index %d is: %d\n", bitArray->getAt(index), index);

	return 0;
}

/**
 * @brief function that checks the binary IO functinality
 * @param bitArray the instance of the BitArary
 * @param const_binary_string holds the string to put inside BitArray storage
 * @param const_binary_string_size the size of the input string
 * @param binary_string string to holds the content from storage
 * @param binary_string_size the size of the output string
 * @return 0 if true, otherwise return value different then 0
*/
int test_binary_IO(BitArray* bitArray, const char* const_binary_string, size_t const_binary_string_size, char* binary_string, size_t binary_string_size) {
	size_t val = 0;
	printf(" - Before binaryIO\nstring is: %s\n", const_binary_string);
	binary_string = (char*)malloc((binary_string_size + 1) * sizeof(char));

	bitArray->fromBinaryStr(const_binary_string, const_binary_string_size);
	binary_string = (char*)malloc((binary_string_size+1) * sizeof(char));
	val = bitArray->toBinaryStr(binary_string, binary_string_size);
	if (val > 1) {
		return handle_error((Error)val);
	}
	printf(" - After binaryIO:\nstring is: %s\n", binary_string);

	return 0;
}

/**
 * @brief function that tests the compare functinoality, return 0 if succeed
 * @param bitArray the instance of the BitArray
 * @param copy the other BitArray to compare to
 * @return 0 if works, otherwise return value different then 0
*/
int test_compare(BitArray* bitArray, BitArray* copy) {
	size_t index = 0, val = 0;

	copy = new BitArray(*bitArray);
	if (copy->getCapacity() == 0) {
		printf("Error copy constructor");
		return 1;
	}
	CHECK_AND_PRINT("value at index %d is: %d\n", bitArray->getAt(index), index);

	val = bitArray->compare(*copy);
	if (val > 1) {
		return handle_error((Error)val);
	}
	printf("comparing check result: %s\n", val ? "false" : "true");
	index = 2;
	copy->setAt(index, true);
	CHECK_AND_PRINT("bitArray1: value at index %d is: %d\n", bitArray->getAt(index), index);
	bitArray->setAt(index, false);
	CHECK_AND_PRINT("bitArray2: value at index %d is: %d\n", bitArray->getAt(index), index);
	val = bitArray->compare(*copy);
	if (val > 1) {
		return handle_error((Error)val);
	}
	printf("comparing check result: %s\n", val ? "false" : "true");

	return 0;
}

/**
 * @brief function that gets BitArray and return its sub array based on given indexes
 * @param bit_array the instance of the BitArray
 * @param sub_array the pointer that will holds the new sub array
 * @param binary_string string that holds the storage of sub array
 * @param binary_string_size the size of the above string
 * @return 0 if works, any other value if fails
*/
int test_sub_array(const BitArray* const bit_array, BitArray* sub_array, char* binary_string, size_t binary_string_size) {
	size_t val = 0;
	size_t first_index = 0, last_index = binary_string_size;
	binary_string = (char*)malloc((binary_string_size + 1) * sizeof(char));

	val = bit_array->toBinaryStr(binary_string, binary_string_size);
	if (val > 1) {
		return handle_error((Error)val);
	}
	printf("array is: %s\n", binary_string);

	*sub_array = *(SpecialMethdos::getSubArray(bit_array, first_index, last_index));
	
	val = sub_array->toBinaryStr(binary_string, (last_index - first_index));
	if (val > 1) {
		return handle_error((Error)val);
	}
	printf("sub array from index %d to index %d is: %s\n",first_index, last_index, binary_string);

	free(binary_string);
	binary_string = NULL;

	return 0;
}

/**
 * @brief function that print the BitArray at hex presentation
 * @param bit_array the first bit array to print
 * @param sub_array the second bit array to print
 * @param binary_string string that holds the sub array storage
 * @param first_index the first index of the sub array
 * @param last_index the last index of the sub array
 * @return 0 if true, otherwise it failes and return different value then 0
*/
int test_print_hex(BitArray* bit_array, BitArray* sub_array, char* binary_string, size_t first_index, size_t last_index) {
	size_t val = 0;
	
	binary_string = (char*)malloc((last_index - first_index + 1) * sizeof(char));
	val = sub_array->toBinaryStr(binary_string, (last_index - first_index));
	if (val > 1) {
		return handle_error((Error)val);
	}
	printf("first is %d, last is %d, sub array is: %s\n", first_index, last_index, binary_string);

	SpecialMethdos::printHex(*bit_array);
	SpecialMethdos::printHex(*sub_array);

	return 0;
}

int main() {
	BitArray* bit_array = new BitArray(), *copy = new BitArray(), *sub_array = new BitArray();;
	size_t val = 0, index = 0, first_index = 0, last_index = 0;
	bool value = false;
	const char* const_binary_string = "100100011000";
	char* binary_string = NULL;
	size_t const_binary_string_size = 12, binary_string_size = 12;

	// test set and get
	if (test_set_get(bit_array)) {
		return 1;
	}

	// test toBinary and fromBinary
	if (test_binary_IO(bit_array, const_binary_string, const_binary_string_size, binary_string, binary_string_size)) {
		return 1;
	}

	// test compare
	if (test_compare(bit_array, copy)) {
		return 1;
	}

	// test getSubArray
	if (test_sub_array(bit_array, sub_array, binary_string, binary_string_size)) {
		return 1;
	}

	// test printHex
	if (bit_array) {
		SpecialMethdos::printHex(*bit_array);
	} 
	if (sub_array) {
		SpecialMethdos::printHex(*sub_array);
	}

	free(binary_string);

	delete copy;
	copy = NULL;
	delete bit_array;
	bit_array = NULL;
	delete sub_array;
	sub_array = NULL;

	return 0;
}
