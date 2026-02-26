#pragma once
#include "BitArray.h"

static class SpecialMethdos {
public:
	static BitArray* GetSubArray( BitArray& bitarray, size_t first, size_t last);

	static void PrintHex(BitArray& bitarray);
};