#pragma once
#include <iostream>

class Matrix
{
private:
	size_t nrows;
	size_t ncols;
	int** matr;

	class Row
	{
	private:
		size_t dim;
		int* row;
	public:
		Row(size_t dim, int* row);
		int& operator[](size_t ind);
	};
public:
	Matrix(size_t nrows, size_t ncols);
	Row operator[](size_t ind);
	Row operator[](size_t ind) const;
	Matrix& operator*=(int tmp);
	bool operator==(const Matrix& other) const;
	bool operator!=(const Matrix& other) const;
	size_t get_row_num() const;
	size_t get_col_num() const;
	~Matrix();
};
