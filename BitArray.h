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

	/**
	 * @brief sets the bit at the given index to the given value
	 * @param index the given location in bits, not in bytes
	 * @param value the given value to be set on the exact location
	*/
	void setAt(size_t index, bool value);

	/**
	 * @brief returns the value of the bit on the given index
	 * @param index the given index to return the value at
	 * @return the value, if it fails, it can return different error codes
	*/
	size_t getAt(size_t index) const;

	/**
	 * @brief function that gets pointer to binary str and fill it with the bits from our storage
	 * @param o_binaryStr the buffer we will fill
	 * @param binaryStrSize the number of bits we want to fill
	 * @return status code of the operation, can return some error status code too
	*/
	size_t toBinaryStr(char* o_binaryStr, size_t binaryStrSize) const;

	/**
	 * @brief function that gets const string and fill the storage with this string, at the length of another given parameter
	 * @param i_binaryStr the const string that holds the characters which will be the bits
	 * @param binaryStrLen the length of string
	 * @return status code of the operation, can return some error status code too
	*/
	size_t fromBinaryStr(const char* i_binaryStr, size_t binaryStrLen);
	
	/**
	 * @brief operator [] to get value by index, same as getAt
	 * @param index the exact location of the bit to get
	 * @return the value of the bit, or error status code if some error occurred.
	*/
	size_t operator[](size_t index) const;

	/**
	 * @brief compare two bit arrays bit by bit, and return result or error status code
	 * @param other the bit array to compare to
	 * @return the result of the comparison (0 equal 1 not equal), or any other error status code if something is wrong
	*/
	size_t compare(const BitArray& other) const;
};
# endif
