# ifndef BITARRAY_H
# define BITARRAY_H

/**
 * @class BitArray
 * @brief Implements array of bits, by storing 8 bits on each byte. Provides set of functions for operations.
 */
class BitArray {
private:
	size_t* m_storage; 
	size_t m_size_bits;	 
	size_t m_capacity_bytes;

	/**
	 * @brief internal method for scaling the capacity of the storage. Can't shrink the capacity, will fail if trying to do so.
	 * @param new_capacity 
	*/
	void scale(size_t new_capacity);

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

	/**
	 * @brief method that returns the actual size of bits
	 * @return the field m_size_bits
	*/
	size_t getSize() const;
};

# endif