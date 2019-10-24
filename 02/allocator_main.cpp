#include <iostream>
#include <cassert>
#include "linear_allocator.h"
using namespace std;

int main()
{
	//Test 1

	LinearAllocator LinAl1(25);
	char* tmp1;
	for (int i = 0; i < 5; i++)
	{
		tmp1 = LinAl1.alloc(5);
		assert(tmp1 != nullptr);
	}

	tmp1 = LinAl1.alloc(5);
	assert(tmp1 == nullptr);

	cout << "Test 1  OK" << endl;


	//Test 2
	LinearAllocator LinAl2(25);
	char* tmp2;
	for (int i = 0; i < 5; i++)
	{
		tmp2 = LinAl2.alloc(5);
		assert(tmp2 != nullptr);
	}

	tmp2 = LinAl2.alloc(5);
	assert(tmp2 == nullptr);

	LinAl2.reset();

	for (int i = 0; i < 5; i++)
	{
		tmp2 = LinAl2.alloc(5);
		assert(tmp2 != nullptr);
	}

	cout << "Test 2  OK" << endl;


	//Test 3
	LinearAllocator LinAl3(0);
	char* tmp3 = LinAl3.alloc(0);
	for (int i = 0; i < 5; i++)
	{
		tmp3 = LinAl3.alloc(0);
		assert(tmp2 != nullptr);
	}

	cout << "Test 3  OK" << endl;

	return 0;
}
