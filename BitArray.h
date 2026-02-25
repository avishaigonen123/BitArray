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
};