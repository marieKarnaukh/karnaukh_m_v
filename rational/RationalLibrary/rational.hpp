#ifndef RATIONALHPP
#define RATIONALHPP

#include <iosfwd>
#include <sstream>

class Rational {
public:
	Rational()
		: num(0), den(1)
	{
		Reduce();
	}
	Rational(int32_t num1 = 0, int32_t den1 = 1)
		: num(num1), den(den1)
	{
		Reduce();
	}
	/*Rational(int32_t num1 = 0)
		: num(num1), den(1)
	{}*/
	Rational(const Rational& rat)  //copy ctor
		: num(rat.num), den(rat.den)
	{}
	~Rational() = default;
	static const char separator = '/';

	std::ostream& write(std::ostream& ostrm) const;
	std::istream& read(std::istream& istrm);
	Rational& operator+=(const Rational& rhs);
	Rational& operator-=(const Rational& rhs);
	Rational& operator+=(const int32_t rhs);
	Rational& operator-=(const int32_t rhs);
	Rational& operator*=(const Rational& rhs);
	Rational& operator*=(const int32_t rhs);
	bool operator==(const Rational& rhs);
	bool operator!=(const Rational& rhs);
	Rational& operator/=(const Rational& rhs);
	int32_t NOD(int32_t x, int32_t y);
	void Reduce();
	

private:
	int32_t num{ 0 };
	int32_t den{ 1 };
};

//declarations

Rational operator+(const Rational& lhs, const Rational& rhs);
Rational operator-(const Rational& lhs, const Rational& rhs);
std::ostream& operator<<(std::ostream& ostrm, const Rational& rhs);
std::istream& operator>>(std::istream& istrm, Rational& rhs);
Rational operator/(const Rational& lhs, const Rational& rhs);
Rational operator*(const Rational& lhs, const Rational& rhs);



#endif