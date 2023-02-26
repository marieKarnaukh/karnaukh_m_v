#include "rational.hpp"
#include <iostream>
#include <sstream>

//definitions

int32_t Rational::NOD(int32_t x, int32_t y) {
	int32_t r = 0;
	while (y != 0)
	{
		r = x % y;
		x = y;
		y = r;
	}
	return x;
}

void Rational::Reduce() {
	int32_t r = NOD(std::abs(num), den);
	num /= r;
	den /= r;
}


Rational& Rational::operator+=(const Rational& rhs) { // += rational
	num *= rhs.den;
	num += rhs.num * den;
	den *= rhs.den;
	Reduce();
	return *this;
}

Rational& Rational::operator+=(const int32_t rhs) {  // += int
	num += rhs * den;
	Reduce();
	return *this;
}

Rational& Rational::operator-=(const Rational& rhs) { //-= rational
	num *= rhs.den;
	num -= rhs.num * den;
	den *= rhs.den;
	Reduce();
	return *this;
}

Rational& Rational::operator-=(const int32_t rhs) { // -= int
	num -= rhs * den;
	Reduce();
	return *this;
}

Rational operator+(const Rational& lhs, const Rational& rhs) { //+
	Rational sum(lhs);
	sum += rhs;
	sum.Reduce();
	return sum;
}

Rational operator-(const Rational& lhs, const Rational& rhs) { //- 
	Rational diff(lhs);
	diff -= rhs;
	diff.Reduce();
	return diff;
}


Rational& Rational::operator*=(const Rational& rhs) { //*= rational
	num *= rhs.num;
	den *= rhs.den;
	Reduce();
	return *this;
}

Rational& Rational::operator*=(const int32_t rhs) { //*= int
	num *= rhs;
	Reduce();
	return *this;
}

Rational& Rational::operator/=(const Rational& rhs) {
	try {
		if (rhs.num == 0)
			throw std::invalid_argument("Division by zero");
		num *= rhs.den;
		den *= std::abs(rhs.num);
		Reduce();
	}
	catch(std::invalid_argument& ex) {
		std::cout << ex.what() << "\n";
	}
	return *this;
}

Rational operator/(const Rational& lhs, const Rational& rhs) {
	Rational ans(lhs);
	ans /= rhs;
	ans.Reduce();
	return ans;
	
}

Rational operator*(const Rational& lhs, const Rational& rhs) {
	Rational ans(lhs);
	ans *= rhs;
	ans.Reduce();
	return ans;
}

bool Rational::operator==(const Rational& rhs) {
	if (num == rhs.num && den == rhs.den)
		return true;
	else return false;
}

bool Rational::operator!=(const Rational& rhs) {
	if (num != rhs.num || den != rhs.den)
		return true;
	else return false;
}

std::ostream& operator<<(std::ostream& ostrm, const Rational& rhs) { //cout<<rhs
	return rhs.write(ostrm);
}


std::istream& operator>>(std::istream& istrm, Rational& rhs) { //cin
	return rhs.read(istrm);
}

std::ostream& Rational::write(std::ostream& ostrm) const {
	ostrm << num << separator << den;
	return ostrm;
}

std::istream& Rational::read(std::istream & istrm)
{
	int32_t num1(0);
	char separator(0);
	int32_t den1(1);
	try {
		istrm >> num1 >> separator >> den1;
		if (istrm.good()) {
			if (Rational::separator == separator && den1 > 0) {
				num = num1;
				den = den1;
				Reduce();
			}
			else {
				if (Rational::separator != separator)
					throw std::invalid_argument("Incorrect input");
				else throw std::invalid_argument("There can be no negative denominator");
			}
		}
		else {
			istrm.setstate(std::ios_base::failbit);
		}
	}
	catch (std::invalid_argument& ex) {
		std::cout << ex.what() << "\n";
	}
	return istrm;
}







