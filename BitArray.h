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

	
};