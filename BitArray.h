#pragma once

class BitArray {
private:
	char* storage;
	size_t size;

public:
	BitArray();
	BitArray(const BitArray& copy);
	~BitArray();

	void SetAt(size_t index, bool value);
	bool GetAt(size_t index) const;

	bool ToBinaryStr(char* o_binaryStr, size_t binaryStrSize) const;
	bool FromBinaryStr(const char* i_binaryStr, size_t binaryStrLen);
};