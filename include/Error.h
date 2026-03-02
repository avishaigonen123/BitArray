#ifndef ERROR_H
#define ERROR_H

/**
 * @brief enum that holds error status codes
*/
enum Error {
	Success = 2, OutOfBound, HeapOverflow, HeapUnderflow, SizeNotMatch, NotBinaryValue
};
// in more complicated version, we'll build Error class, like exception class

#endif
