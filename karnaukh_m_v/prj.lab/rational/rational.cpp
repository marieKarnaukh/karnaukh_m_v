#include <rational/rational.hpp>
#include <iostream>
#include <sstream>

std::ostream& operator<<(std::ostream& ostrm, const Rational& rhs) { //cout<<rhs
    return rhs.WriteTo(ostrm);
}


std::istream& operator>>(std::istream& istrm, Rational& rhs) { //cin
    return rhs.ReadFrom(istrm);
}

//definitions

Rational::Rational()
    : num(0), den(1)
{}
Rational::Rational(const int32_t num1)
    : num(num1), den(1)
{}
Rational::Rational(const int32_t num1, const int32_t den1) {
    if (den1 == 0) {
        throw std::invalid_argument("Division by zero");
    }
    if (den1 < 0)
    {
        num = -num1;
        den = -den1;
    }
    else {
        num = num1;
        den = den1;
    }
    Reduce();
}
Rational::Rational(const Rational& rat)  //copy ctor
    : num(rat.num), den(rat.den)
{}

Rational& Rational::operator=(const Rational& rhs) {
    num = rhs.num;
    den = rhs.den;
    return *this;
}

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

Rational Rational::operator-() {
    Rational newR(*this);
    newR.num = -num;
    return newR;
}


Rational& Rational::operator+=(const Rational& rhs) { // += rational
    num *= rhs.den;
    num += rhs.num * den;
    den *= rhs.den;
    Reduce();
    return *this;
}

Rational& Rational::operator+=(const int32_t& rhs) {  // += int
    Rational tmp(rhs);
    num = tmp.den * num + tmp.num * den;
    den *= tmp.den;
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

Rational& Rational::operator-=(const int32_t& rhs) { // -= int
    Rational tmp(rhs);
    num = tmp.den * num - tmp.num * den;
    den *= tmp.den;
    Reduce();
    return *this;
}

Rational& Rational::operator*=(const Rational& rhs) { //*= rational
    num *= rhs.num;
    den *= rhs.den;
    Reduce();
    return *this;
}

Rational& Rational::operator*=(const int32_t& rhs) { //*= int
    num *= rhs;
    Reduce();
    return *this;
}

Rational& Rational::operator/=(const Rational& rhs) {
    if (rhs.num == 0) {
        throw std::invalid_argument("Division by zero");
    }
    num *= rhs.den; // num *= rhs.den * (rhs.num / std::abs(rhs.num));
    den *= rhs.num; // den *= std::abs(rhs.num);
    Reduce();
    return *this;
}

Rational& Rational::operator/=(const int32_t& rhs)
{
    if(rhs == 0)
    {
        throw std::invalid_argument("division by zero");
    }
    den *= rhs;
    Reduce();
    return *this;
}

bool operator==(const Rational& lhs, const Rational& rhs)
{
    Rational tmp(lhs);
    tmp -= rhs;
    return (tmp.getNum() == 0);
}

bool operator==(const int32_t& lhs, const Rational& rhs)
{
    Rational tmp(lhs);
    tmp -= rhs;
    return (tmp.getNum() == 0);
}

bool operator==(const Rational& lhs, const int32_t& rhs)
{
    Rational tmp(lhs);
    tmp -= rhs;
    return (tmp.getNum() == 0);
}

bool operator!=(const Rational& lhs, const Rational& rhs)
{
    Rational tmp(lhs);
    tmp -= rhs;
    return (tmp.getNum() != 0);
}

bool operator!=(const int32_t& lhs, const Rational& rhs)
{
    Rational tmp(lhs);
    tmp -= rhs;
    return (tmp.getNum() != 0);
}

bool operator!=(const Rational& lhs, const int32_t& rhs)
{
    Rational tmp(lhs);
    tmp -= rhs;
    return (tmp.getNum() != 0);
}

bool operator>(const Rational& lhs, const Rational& rhs)
{
    Rational tmp(lhs);
    tmp -= rhs;
    return (tmp.getNum() > 0);
}

bool operator>(const int32_t& lhs, const Rational& rhs)
{
    Rational tmp(lhs);
    tmp -= rhs;
    return (tmp.getNum() > 0);
}

bool operator>(const Rational& lhs, const int32_t& rhs)
{
    Rational tmp(lhs);
    tmp -= rhs;
    return (tmp.getNum() > 0);
}

bool operator>=(const Rational& lhs, const Rational& rhs)
{
    Rational tmp(lhs);
    tmp -= rhs;
    return (tmp.getNum() >= 0);
}

bool operator>=(const int32_t& lhs, const Rational& rhs)
{
    Rational tmp(lhs);
    tmp -= rhs;
    return (tmp.getNum() >= 0);
}

bool operator>=(const Rational& lhs, const int32_t& rhs)
{
    Rational tmp(lhs);
    tmp -= rhs;
    return (tmp.getNum() >= 0);
}

bool operator<(const Rational& lhs, const Rational& rhs)
{
    Rational tmp(rhs);
    tmp -= lhs;
    return (tmp.getNum() > 0);
}

bool operator<(const int32_t& lhs, const Rational& rhs)
{
    Rational tmp(rhs);
    tmp -= lhs;
    return (tmp.getNum() > 0);
}

bool operator<(const Rational& lhs, const int32_t& rhs)
{
    Rational tmp(rhs);
    tmp -= lhs;
    return (tmp.getNum() > 0);
}

bool operator<=(const Rational& lhs, const Rational& rhs)
{
    Rational tmp(rhs);
    tmp -= lhs;
    return (tmp.getNum() >= 0);
}

bool operator<=(const int32_t& lhs, const Rational& rhs)
{
    Rational tmp(rhs);
    tmp -= lhs;
    return (tmp.getNum() >= 0);
}

bool operator<=(const Rational& lhs, const int32_t& rhs)
{
    Rational tmp(rhs);
    tmp -= lhs;
    return (tmp.getNum() >= 0);
}

Rational operator+(const Rational& lhs, const Rational& rhs) { //+
    Rational sum(lhs);
    sum += rhs;
    sum.Reduce();
    return sum;
}

Rational operator+(const Rational& lhs, const int32_t rhs)
{
    Rational sum(lhs);
    sum += rhs;
    sum.Reduce();
    return sum;
}

Rational operator+(const int32_t lhs, const Rational& rhs)
{
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

Rational operator-(const Rational& lhs, const int32_t rhs)
{
    Rational diff(lhs);
    diff -= rhs;
    diff.Reduce();
    return diff;
}

Rational operator-(const int32_t lhs, const Rational& rhs)
{
    Rational diff(lhs);
    diff -= rhs;
    diff.Reduce();
    return diff;
}

Rational operator*(const Rational& lhs, const Rational& rhs) {
    Rational ans(lhs);
    ans *= rhs;
    ans.Reduce();
    return ans;
}

Rational operator*(const Rational& lhs, const int32_t rhs)
{
    Rational mult(lhs);
    mult *= rhs;
    mult.Reduce();
    return mult;
}

Rational operator*(const int32_t lhs, const Rational& rhs)
{
    Rational mult(lhs);
    mult *= rhs;
    mult.Reduce();
    return mult;
}

Rational operator/(const Rational& lhs, const Rational& rhs) {
    Rational ans(lhs);
    ans /= rhs;
    ans.Reduce();
    return ans;
}

Rational operator/(const Rational& lhs, const int32_t rhs)
{
    if(rhs == 0) {
        throw std::invalid_argument("division by zero");
    }
    Rational div(lhs);
    div /= rhs;
    div.Reduce();
    return div;
}

Rational operator/(const int32_t lhs, const Rational& rhs)
{
    Rational div(lhs);
    div /= rhs;
    div.Reduce();
    return div;
}

Rational& Rational::operator++()
{
    num += den;
    Reduce();
    return *this;
}

Rational Rational::operator++(int)
{
    Rational oldValue(*this);
    ++(*this);
    return oldValue;
}

Rational& Rational::operator--()
{
    num -= den;
    Reduce();
    return *this;
}

Rational Rational::operator--(int)
{
    Rational oldValue(*this);
    --(*this);
    return oldValue;
}

std::ostream& Rational::WriteTo(std::ostream& ostrm) const {
    ostrm << num << separator << den;
    return ostrm;
}

std::istream& Rational::ReadFrom(std::istream& istrm) {
    int32_t numInp(0);
    int32_t denInp(0);
    char ch(' ');
    char sep('/');
    bool isNegative(false);

    while (std::isspace(istrm.peek())) {
        ch = istrm.get();
    }
    if (istrm.peek() == '-') {
        isNegative = true;
        ch = istrm.get();
    }
    while (std::isdigit(istrm.peek())) {
        ch = istrm.get();
        numInp *= 10;
        numInp += static_cast<int>(ch - '0');
    }
    if (ch == '-') {
        istrm.setstate(std::ios_base::failbit);
        return istrm;
    }
    if (istrm.peek() != sep) {
        istrm.setstate(std::ios_base::failbit);
    }
    ch = istrm.get();
    while (std::isdigit(istrm.peek())) {
        ch = istrm.get();
        denInp *= 10;
        denInp += static_cast<int>(ch - '0');
    }
    if (ch == sep) {
        istrm.setstate(std::ios_base::failbit);
        return istrm;
    }
    if (istrm.good() || istrm.eof()) {
        if (denInp == 0) {
            istrm.setstate(std::ios_base::failbit);
            return istrm;
        }
        num = numInp;
        den = denInp;
        if (isNegative) {
            num *= -1;
        }
        Reduce();
    }
    return istrm;
}
