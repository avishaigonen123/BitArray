# ifndef BITARRAY_H
# define BITARRAY_H

/**
 * @class BitArray
 * @brief Implements array of bits, by storing 8 bits on each byte. Provides set of functions for operations.
 */
class BitArray {
private:
	size_t* storage; // holds bytes, unsigned ints
	size_t size;	 // how much bits
	size_t capacity; // how much bytes


	void resize(size_t new_capacity); // private method for resize the capacity

public:
	/**
	 * @brief constructor, creates storage with capacity of 1 byte, and empty values.
	*/
	BitArray();

	/**
	 * @brief copy ctor, deep copy of all fields.
	*/
	BitArray(const BitArray& copy);

	/**
	 * @brief dtor, free the storage allocated memory
	*/
	~BitArray();

	size_t getSize() const;

	
};