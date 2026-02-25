#pragma once

class BitArray {
private:
	char* storage;
	size_t size;

public:
	BitArray();
	BitArray(const BitArray& copy);
	~BitArray();

	
};