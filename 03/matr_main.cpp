#include <cassert>
#include "matr.h"

using namespace std;

int main()
{
	//Test 1
	Matrix M1(5, 6);
	Matrix M2(5, 6);
	for (size_t i = 0; i < M1.get_row_num(); i++)
	{
		for (size_t j = 0; j < M1.get_col_num(); j++)
		{
			M1[i][j] = i + j + 1;
			M2[i][j] = i + j + 1;
		}
	}
	assert(M1 == M2);
	assert((M1.get_row_num() == 5) && (M1.get_col_num() == 6));
	assert(M1[4][5] == 10);

	cout << "Test 1  OK" << endl;


	//Test 2
	Matrix M3(7, 7);
	Matrix M4(7, 7);
	for (size_t i = 0; i < M3.get_row_num(); i++)
	{
		for (size_t j = 0; j < M3.get_col_num(); j++)
		{
			M3[i][j] = i + j + 1;
			M4[i][j] = i + j + 1;
		}
	}
	M3 *= 2;
	assert(M3 != M4);

	cout << "Test 2  OK" << endl;

	return 0;
}
