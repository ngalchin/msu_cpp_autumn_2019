#include "linear_allocator.h"

LinearAllocator::LinearAllocator(size_t maxSize): maxSize(maxSize)
{
	base = new char[maxSize];
	free = base;
	end = base + maxSize - 1;
}

char* LinearAllocator::alloc(size_t size)
{
	if (size + free > end + 1)
	{
		return nullptr;
	}
	else
	{
		char* tmp = free;
		free += size;
		return tmp;
	}
}

void LinearAllocator::reset()
{
	free = base;
}

LinearAllocator::~LinearAllocator()
{
	delete [] base;
}
