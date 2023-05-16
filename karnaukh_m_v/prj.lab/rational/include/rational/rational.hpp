#ifndef RATIONALHPP
#define RATIONALHPP

#include <iosfwd>
#include <sstream>
#include <cstdint>

class Rational {
public:
	Rational();
	explicit Rational(const int32_t num1);
	Rational(Rational&&) = default;
	Rational(const int32_t num1, const int32_t den1);
	Rational(const Rational& rat);
	~Rational() = default;
	static const char separator = '/';

	Rational& operator=(const Rational& rhs);
	Rational& operator=(Rational&&) = default;
	std::ostream& WriteTo(std::ostream& ostrm) const;
	std::istream& ReadFrom(std::istream& istrm);
	Rational operator-();
	Rational& operator+=(const Rational& rhs);
	Rational& operator-=(const Rational& rhs);
	Rational& operator+=(const int32_t& rhs);
	Rational& operator-=(const int32_t& rhs);
	Rational& operator*=(const Rational& rhs);
	Rational& operator*=(const int32_t& rhs);
	Rational& operator/=(const Rational& rhs);
    Rational& operator/=(const int32_t& rhs);
	Rational& operator++();
	Rational operator++(int);
	Rational& operator--();
	Rational operator--(int);
	int32_t NOD(int32_t x, int32_t y);
	void Reduce();
	
	const int32_t& getNum() const { return num; }
	const int32_t& getDen() const { return den; }

private:
	int32_t num{0};
	int32_t den{1};
};

//declarations

std::ostream& operator<<(std::ostream& ostrm, const Rational& rhs);
std::istream& operator>>(std::istream& istrm, Rational& rhs);

Rational operator+(const Rational& lhs, const Rational& rhs);
Rational operator+(const Rational& lhs, const int32_t rhs); 
Rational operator+(const int32_t lhs, const Rational& rhs);
Rational operator-(const Rational& lhs, const Rational& rhs);
Rational operator-(const Rational& lhs, const int32_t rhs);
Rational operator-(const int32_t lhs, const Rational& rhs);
Rational operator*(const Rational& lhs, const Rational& rhs);
Rational operator*(const Rational& lhs, const int32_t rhs);
Rational operator*(const int32_t lhs, const Rational& rhs);
Rational operator/(const Rational& lhs, const Rational& rhs);
Rational operator/(const Rational& lhs, const int32_t rhs);
Rational operator/(const int32_t lhs, const Rational& rhs);

bool operator==(const Rational& lhs, const Rational& rhs);
bool operator==(const int32_t& lhs, const Rational& rhs);
bool operator==(const Rational& lhs, const int32_t& rhs);

bool operator!=(const Rational& lhs, const Rational& rhs);
bool operator!=(const int32_t& lhs, const Rational& rhs);
bool operator!=(const Rational& lhs, const int32_t& rhs);

bool operator>(const Rational& lhs, const Rational& rhs);
bool operator>(const int32_t& lhs, const Rational& rhs);
bool operator>(const Rational& lhs, const int32_t& rhs);

bool operator>=(const Rational& lhs, const Rational& rhs);
bool operator>=(const int32_t& lhs, const Rational& rhs);
bool operator>=(const Rational& lhs, const int32_t& rhs);

bool operator<(const Rational& lhs, const Rational& rhs);
bool operator<(const int32_t& lhs, const Rational& rhs);
bool operator<(const Rational& lhs, const int32_t& rhs);

bool operator<=(const Rational& lhs, const Rational& rhs);
bool operator<=(const int32_t& lhs, const Rational& rhs);
bool operator<=(const Rational& lhs, const int32_t& rhs);

#endif
