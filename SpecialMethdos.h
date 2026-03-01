#ifndef SPECIAL_METHODS_H
#define SPECIAL_METHODS_H
#include "BitArray.h"

/**
 * @brief static class for special methods like get sub array and print hex
*/
static class SpecialMethdos {
public:
	/**
	 * @brief function that gets bitarray and first + last indexes, and then returns sub array
	 * @param bitarray the big bit array
	 * @param first index where the sub array starts
	 * @param last index where the sub array ends
	 * @return pointer to the created sub array
	*/
	static BitArray* getSubArray(const BitArray& bitarray, size_t first, size_t last);

	/**
	 * @brief function that prints the sub array it gets in hex format
	 * @param bitarray the sub array it gets for printing
	*/
	static void printHex(const BitArray& bitarray);
};
#endif
