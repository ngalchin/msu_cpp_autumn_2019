#include <cassert>
#include "BigInt.h"

using namespace std;

int main()
{
	//Test 1
	BigInt a = 123;
	BigInt b = 912;

	assert(a + b == 1035);
	assert(a - b == -789);
	assert(a < b);
	assert(a <= b);
	assert(!(a > b));
	assert(!(a >= b));
	
	cout << a + b << endl;
	cout << a - b << endl;


	cout << "Test 1  OK" << endl;

	//Test 2
	BigInt c("10000000000000000000000000000000000000000000000000000000000000000"); //10^65
	BigInt d("22000000000000000000000000000000000000000000000000000000000000000");
	BigInt e("32000000000000000000000000000000000000000000000000000000000000000");
	
	assert(c + d == e);

	cout << c << endl;
	cout << d << endl;
	cout << c + d << endl;
	cout << d - c << endl;
	

	cout << "Test 2  OK" << endl;

	return 0;
}
