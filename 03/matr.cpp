#include "matr.h"

Matrix::Row::Row(size_t dim, int* row): dim(dim), row(row) {}

int& Matrix::Row::operator[](size_t ind)
{
	if (ind >= dim)
		throw std::out_of_range("");
	return row[ind];
}

Matrix::Matrix(size_t nrows, size_t ncols): nrows(nrows), ncols(ncols)
{
	matr = new int*[nrows];
	for (size_t i = 0; i < nrows; i++)
		matr[i] = new int[ncols];
}

Matrix::Row Matrix::operator[](size_t ind)
{
	if (ind >= nrows)
		throw std::out_of_range("");
	return Row(ncols, matr[ind]);
}

Matrix& Matrix::operator*=(int tmp)
{
	for (size_t i = 0; i < nrows; i++)
		for (size_t j = 0; j < ncols; j++)
			matr[i][j] *= tmp;
	return *this;
}

bool Matrix::operator==(const Matrix& other) const
{
	if (this == &other)
		return true;
	if (nrows != other.nrows || ncols != other.ncols)
		return false;
	for (size_t i = 0; i < nrows; i++)
		for (size_t j = 0; j < ncols; j++)
			if (matr[i][j] != other.matr[i][j])
				return false;
	return true;
}

bool Matrix::operator!=(const Matrix& other) const {return !(*this == other); }

size_t Matrix::get_col_num() const {return ncols; }

size_t Matrix::get_row_num() const {return nrows; }

Matrix::~Matrix()
{
	for (size_t i = 0; i < nrows; i++)
		delete [] matr[i];
	delete [] matr;
}
