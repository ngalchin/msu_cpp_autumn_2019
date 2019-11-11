#include "BigInt.h"

BigInt::BigInt(int num): negative(num < 0)
{
	std::string tmp;
	if (negative)
	{
		tmp = std::to_string(-num);
	}
	else
	{
		tmp = std::to_string(num);
	}
	size = tmp.length();
	number = new char [size];
	for (size_t i = 0; i < size; i++)
		number[i] = tmp[i];
}

BigInt::BigInt(): negative(false), number(nullptr), size(0) {}

BigInt::BigInt(const std::string& str)
{
	std::string tmp;
	if (str[0] == '-')
	{
		negative = true;
		size = str.length() - 1;
		tmp = str.substr(1, size);
	}
	else
	{
		negative = false;
		size = str.length();
		tmp = str;
	}
	number  = new char[size];
	for (size_t i = 0; i < size; i++ )
		number[i] = tmp[i];
}

BigInt::BigInt(const BigInt& big_num): size(big_num.size), negative(big_num.negative)
{
	number = new char [size];
	std::memcpy(number, big_num.number, size);
}

BigInt::BigInt(BigInt&& moved)
{
	negative = moved.negative;
	size = moved.size;
	number = moved.number;
	moved.negative = false;
	moved.size = 0;
	moved.number = nullptr;
}

BigInt& BigInt::operator=(const BigInt& big_num)
{
	if (this == &big_num)
		return *this;
	delete [] number;
	negative = big_num.negative;
    size = big_num.size;
    char* ptr = new char[size];
    number = ptr;
    std::copy(big_num.number, big_num.number + size, number);
    return *this;
}

BigInt& BigInt::operator=(BigInt&& moved)
{
	if (this == &moved)
        return *this;
    negative = moved.negative;
    size = moved.size;
    delete [] number;
    number = moved.number;
    moved.number = nullptr;
    moved.size = 0;
    moved.negative = false;
    return *this;
}

BigInt BigInt::operator-() const 
{
	BigInt tmp = *this;
	tmp.negative = !(this->negative);
	return tmp;
}

bool BigInt::operator==(const BigInt& big_num) const
{
	if (negative == big_num.negative && size == big_num.size)
	{
		for(size_t i = 0; i < size; i++)
		{
			if (number[i] != big_num.number[i])
				return false;
		}
		return true;
	}
	return false;
}

bool BigInt::operator!=(const BigInt& big_num) const
{
	return !(*this == big_num);
}

bool BigInt::operator<(const BigInt& big_num) const
{
	if (negative != big_num.negative)
	{
		return negative;
	}
	else
	{
		if (size != big_num.size)
		{
			if (negative)
				return (size > big_num.size);
			else
				return (size < big_num.size); 
		}else
		{
			if (negative)
			{
				for (size_t i = 0; i < size; i++)
				{
					if (number[i] > big_num.number[i])
						return true;
					else if (number[i] < big_num.number[i])
						return false;
				}
				return false;
			}
			else
			{
				for (size_t i = 0; i < size; i++)
				{
					if (number[i] < big_num.number[i])
						return true;
					else if (number[i] > big_num.number[i])
						return false;
				}
				return false;
			}
		}
	}
}

bool BigInt::operator<=(const BigInt& big_num) const
{
	return ((*this < big_num) || (*this == big_num));
}

bool BigInt::operator>(const BigInt& big_num) const
{
	return (!(*this < big_num) && (*this != big_num));
}

bool BigInt::operator>=(const BigInt& big_num) const
{
	return (!(*this < big_num));
}

BigInt operator+(const BigInt& l_num, const BigInt& r_num)
{
	if (!l_num.negative && !r_num.negative)
	{
		BigInt tmp;
		int max_size = std::max(l_num.size, r_num.size) + 1;
		int* sum = new int[max_size];
		for (size_t i = 0; i < max_size; i++)
			sum[i] = 0;

		for (size_t i = 0; i < max_size - 1; i++)
		{
			if (l_num.size >= 1 + i)
				sum[max_size - 1 - i] += (l_num.number[l_num.size - 1 - i] - '0');
			if (r_num.size >= 1 + i)
				sum[max_size - 1 - i] += (r_num.number[r_num.size - 1 - i] - '0');
			sum[max_size - 2 - i] = sum[max_size - 1 - i] / 10;
			sum[max_size - 1 - i] = sum[max_size - 1 - i] % 10;
		}
		if (sum[0] == 0)
		{
			tmp.size = max_size - 1;
			tmp.number = new char[tmp.size];
			for (size_t i = 0; i < tmp.size; i++)
				tmp.number[i] = sum[i + 1] + '0';
		}
		else
		{
			tmp.size = max_size;
			tmp.number = new char[tmp.size];
			for (size_t i = 0; i < tmp.size; i++)
				tmp.number[i] = sum[i] + '0';
		}
		delete [] sum;
		return tmp;
	}
	else if (l_num.negative && r_num.negative)
		return -((-l_num) + (-r_num));
	else if (l_num.negative && !r_num.negative)
		return (r_num - (-l_num));
	else if (!l_num.negative && r_num.negative)
		return (l_num - (-r_num));
}

BigInt operator-(const BigInt& l_num, const BigInt& r_num)
{
	if (!l_num.negative && !r_num.negative)
	{
		if (r_num > l_num)
			return -(r_num - l_num);
		size_t max_size = l_num.size;
		int* diff = new int[max_size];
		for (size_t i = 0; i < max_size; i++)
			diff[i] = l_num.number[i] - '0';
		for (size_t i = 0; i < max_size - 1; i++)
		{
			if (r_num.size >= i + 1)
				diff[max_size - 1 - i] -= r_num.number[r_num.size - 1 - i] - '0';
			if (diff[max_size - 1 - i] < 0)
			{
				diff[max_size - 1 - i] += 10;
				diff[max_size - 2 - i] -= 1;
			}
		}
		if (r_num.size == max_size)
			diff[0] -= r_num.number[0] - '0';
		size_t diff_size = max_size;

		for (size_t i = 0; i < max_size; i++)
		{
			if (diff[i] == 0)
				diff_size -= 1;
			else
				break;
		}
		BigInt tmp = l_num;
		tmp.size = diff_size;
		for (size_t i = 0; i < tmp.size; i++)
			tmp.number[tmp.size - 1 - i] = diff[max_size - 1 - i] + '0';
		delete [] diff;
		return tmp;
	}
	else if (r_num.negative)
		return (l_num + (-r_num));
	else if (l_num.negative && !r_num.negative)
		return -((-l_num) + r_num);
}

std::ostream& operator<<(std::ostream &out, const BigInt& big_num)
{
    if (big_num.negative)
        out << '-';
    for (size_t i = 0; i < big_num.size; i++)
        out << big_num.number[i];
    out << std::endl;
    return out;
}
BigInt::~BigInt(){ delete [] number;};
