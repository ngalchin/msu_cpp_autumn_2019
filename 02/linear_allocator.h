#pragma once
#include <cstdlib>

class LinearAllocator
{
private:
	size_t maxSize;
	char* base;
	char* free;
	char* end;
public:
    LinearAllocator(size_t maxSize);
    char* alloc(size_t size);
    void reset();
    ~LinearAllocator();
};
