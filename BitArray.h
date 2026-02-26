#pragma once

class BitArray {
private:
	size_t* storage; // holds bytes, unsigned ints
	size_t size;	 // how much bits
	size_t capacity; // how much bytes


	void resize(size_t new_capacity); // private method for resize the capacity

public:
	BitArray();
	BitArray(const BitArray& copy);
	~BitArray();

	size_t getSize() const;
	size_t GetAt(size_t index) const;
	void SetAt(size_t index, bool value);

	size_t ToBinaryStr(char* o_binaryStr, size_t binaryStrSize) const;
	size_t FromBinaryStr(const char* i_binaryStr, size_t binaryStrLen);
	
	size_t operator[](size_t index) const;

	size_t compare(const BitArray& other) const;
};