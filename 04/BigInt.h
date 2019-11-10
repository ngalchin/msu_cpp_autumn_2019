#pragma once
#include <iostream>
#include <cstring>

class BigInt
{

private:
	size_t size;
	char* number;
	bool negative;
public:
	BigInt(int num);
	BigInt();
	BigInt(const std::string& str);
	BigInt(const BigInt& big_num);
	BigInt(BigInt&& moved);

	BigInt& operator=(const BigInt& big_num);
	BigInt& operator=(BigInt&& moved);

	BigInt operator-() const;
	bool operator==(const BigInt& big_num) const;
	bool operator!=(const BigInt& big_num) const;
    	bool operator<(const BigInt& big_num) const;
    	bool operator<=(const BigInt& big_num) const;
    	bool operator>(const BigInt& big_num) const;
    	bool operator>=(const BigInt& big_num) const;

    	friend BigInt operator+(const BigInt& l_num, const BigInt& r_num);
    	friend BigInt operator-(const BigInt& l_num, const BigInt& r_num);
    	friend std::ostream& operator<<(std::ostream& out, const BigInt& big_num);
	~BigInt();
};
