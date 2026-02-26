#pragma once
#include "stdio.h"

enum Error {
	Success = 2, OutOfBound, HeapOverflow, HeapUnderflow, SizeNotMatch
};

// in more complicated version, we'll build Error class, like exception class


