# ifndef BITARRAY_H
# define BITARRAY_H

// The class BitArray implement array of bits, by storing 8 bits on each byte. 
// It provides set of functions that gives various functionallity to dealing with the array.
class BitArray {
private:
	size_t* m_storage; // holds bytes, unsigned ints
	size_t m_size;	 // how much bits
	size_t m_capacity; // how much bytes


	void resize(size_t new_capacity); // private method for resize the capacity

public:
	BitArray();
	BitArray(const BitArray& copy);
	~BitArray();

	size_t getSize() const;
};

# endif