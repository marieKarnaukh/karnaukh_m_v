#include <rational/rational.hpp>
#include <iostream>
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>

TEST_CASE("[rational] - Rational ctor")
{
    CHECK(Rational() == Rational(0, 1));
    CHECK(Rational(-3) == Rational(-3, 1));
    CHECK(Rational(10, 6) == Rational(5, 3));
    CHECK(Rational(-10, 6) == Rational(-5, 3));
    CHECK(Rational(10, -6) == Rational(-5, 3));
    CHECK(Rational(-10, -6) == Rational(5, 3));
    CHECK_THROWS(Rational(1, 0));

    CHECK(Rational(3) == Rational(3, 1));
    CHECK(Rational(3) >= Rational(3, 1));
    CHECK(Rational(3) <= Rational(3, 1));
    CHECK(Rational(-10, -6) != Rational(-5, 3));
    CHECK(Rational(10, 5) > Rational(10, 6));
    CHECK(Rational(10, -7) > Rational(-10, 6));
    CHECK(Rational(5, 10) + Rational(-25, 50) <= Rational());
}

Rational ct1(1 / 3);
Rational ctor = ct1;

TEST_CASE("copy ctor")
{
    CHECK(ctor == Rational(1 / 3));
}

TEST_CASE("Arithmetic")
{
    CHECK(Rational(5, 6) == Rational(1, 3) + Rational(1, 2));
    CHECK(Rational(-1, 6) == Rational(1, 3) - Rational(1, 2));
    CHECK(Rational(2, 3) == Rational(1, 3) / Rational(1, 2));
    CHECK(Rational(1, 6) == Rational(1, 3) * Rational(1, 2));
}

TEST_CASE("comparisons")
{
    CHECK(Rational(1, 3) >= Rational(1, 3));
    CHECK(Rational(1, 3) <= Rational(1, 3));
    CHECK(Rational(1, 3) > Rational(1, 6));
    CHECK(Rational(1, 6) < Rational(1, 3));
}

TEST_CASE("Comparison")
{
    CHECK(true == (Rational(1, 3) == Rational(1, 3)));
    CHECK(true == (Rational(1, 3) != Rational(1, 2)));
    CHECK((Rational(1, 3) > Rational(1, 3)) == false);
    CHECK((Rational(1, 3) < Rational(1, 3)) == false);
    CHECK((Rational(1, 3) >= Rational(1, 3)) == true);
    CHECK((Rational(1, 3) <= Rational(1, 3)) == true);
    CHECK(Rational() == Rational(0));
    CHECK(Rational() == Rational(0, -1));
}

TEST_CASE("Reducing")
{
    CHECK(Rational(9, 3) == Rational(3, 1));
    CHECK(Rational(-9, 3) == Rational(-3, 1));
    CHECK(Rational(9, -3) == Rational(-3, 1));
    CHECK(Rational(-9, -3) == Rational(3, 1));
}

Rational ct = Rational(3, 9);
TEST_CASE("Ctor")
{
    CHECK(Rational(0) == Rational(0, 1));
    CHECK(Rational(3, 9) == ct);
}

TEST_CASE("unary oerations")
{
    CHECK(++Rational(1, 5) == Rational(6, 5));
    --Rational(1, 5);
    CHECK(Rational(1, 5)++ == Rational(1, 5));
    --Rational(1, 5);
    CHECK(--Rational(1, 5) == Rational(-4, 5));
    ++Rational(1, 5);
    CHECK(Rational(1, 5)-- == Rational(1, 5));
    ++Rational(1, 5);

    CHECK(++Rational(-1, 5) == Rational(4, 5));
    --Rational(-1, 5);
    CHECK(Rational(-1, 5)++ == Rational(-1, 5));
    --Rational(-1, 5);
    CHECK(--Rational(-1, 5) == Rational(-6, 5));
    ++Rational(-1, 5);
    CHECK(Rational(-1, 5)-- == Rational(-1, 5));
    ++Rational(-1, 5);

    CHECK(++Rational(5) == Rational(6, 1));
    --Rational(5);
    CHECK(Rational(5)++ == Rational(5, 1));
    --Rational(5);
    CHECK(--Rational(5) == Rational(4, 1));
    ++Rational(5);
    CHECK(Rational(5)-- == Rational(5, 1));
    ++Rational(5);
}

Rational ratt(4, 10); // 2/5
int32_t int1 = 2;
int32_t int2 = -1;
int32_t int3 = 0;

TEST_CASE("int arithmetics")
{
    CHECK(ratt + int1 == Rational(12, 5));
    CHECK(ratt - int1 == Rational(-8, 5));
    CHECK(ratt * int1 == Rational(4, 5));
    CHECK(int1 * ratt == Rational(4, 5));
    CHECK(ratt / int1 == Rational(1, 5));
    CHECK(int1 / ratt == Rational(5, 1));

    CHECK(ratt + int2 == Rational(-3, 5));
    CHECK(ratt - int2 == Rational(7, 5));
    CHECK(ratt * int2 == Rational(-2, 5));
    CHECK(int2 * ratt == Rational(-2, 5));
    CHECK(ratt / int2 == Rational(-2, 5));
    CHECK(int2 / ratt == Rational(-5, 2));

    CHECK(ratt + int3 == Rational(2, 5));
    CHECK(ratt - int3 == Rational(2, 5));
    CHECK(ratt * int3 == Rational(0));
    CHECK(int3 * ratt == Rational());
    CHECK(int3 / ratt == Rational(0));
    CHECK_THROWS(ratt / int3 == Rational());
}

TEST_CASE("compound assignment")
{
    CHECK(Rational(5, 6) == (Rational(1, 2) += Rational(1, 3)));
    CHECK(Rational(1, 2) + 2 == Rational(5, 2));
    CHECK(Rational(5, 2) == (Rational(1, 2) += 2));
    CHECK(-1 == (Rational(1, 2) += Rational(-3, 2)));

    CHECK(Rational(1, 6) == (Rational(1, 2) -= Rational(1, 3)));
    CHECK(Rational(1, 6) == (Rational(1, 2) *= Rational(1, 3)));
    CHECK(Rational(3, 2) == (Rational(1, 2) /= Rational(1, 3)));
}

/************** i/o test **************/
/*
bool testParse(const std::string& str) {
    using namespace std;
    istringstream istrm(str);
    Rational rat;
    istrm >> rat;
    if (istrm.good()) {
        cout << "Read success: " << str << " -> " << rat << endl;
    }
    else {
        cout << "Read error: " << str << " -> " << rat << endl;
    }
    return istrm.good();
}

TEST_CASE("i/o test") {
    Rational test1;
    Rational test2;
    try {
        std::cin >> test1 >> test2;
        std::cout << test1 << std::endl;
        std::cout << test2 << std::endl;
        std::cout << (test1 == test2) << '\n';
    }
    catch (const std::exception& ex) {
        std::cerr << ex.what() << '\n';
    }
}

TEST_CASE("test parse") {
    using namespace std;
    Rational test;
    test += Rational(9 / 8);
    testParse("7/9");
    testParse("2/-5");
    testParse("1/0");
}*/

TEST_CASE("Test Rational operator>>") {
    Rational r;
    std::stringstream ss("-4/10");
    ss >> r;
    // r.ReadFrom(ss);
    CHECK(r.getNum() == -2);
    CHECK(r.getDen() == 5);
    // Rational num(1, 3);
    // CHECK(num == r);
    // CHECK(Rational(7, 9) == r);
}

/*
TEST_CASE("[rational] - Rational ctor") {
	CHECK(Rational() == Rational(0, 1));
	CHECK(Rational(3) == Rational(3, 1));
	CHECK(Rational(-3) == Rational(-3, 1));
	CHECK(Rational(10, 6) != Rational(-5, 3));
	CHECK(Rational(-10, 6) >= Rational(-5, 3));
	CHECK(Rational(10, -6) == Rational(-5, 3));
	CHECK(Rational(-10, -6) == Rational(5, 3));
	CHECK_THROWS(Rational(1, 0));
}

Rational rat1(1, 3);
Rational rat2(1, 2);

Rational sum(5, 6);
Rational diff(-1, 6);
Rational divv(2, 3);
Rational mul(1, 6);


TEST_CASE("Arithmetic") {
	CHECK(sum == rat1 + rat2);
	CHECK(diff == rat1 - rat2);
	CHECK(divv == rat1 / rat2);
	CHECK(mul == rat1 * rat2);
}

bool equal = true;
Rational rat3 = rat1;
Rational rat6(1, 6);

TEST_CASE("123") {
	CHECK(rat1 >= rat3);
	CHECK(rat1 <= rat3);
	CHECK(rat1 > rat6);
	CHECK(rat6 < rat3);
}

TEST_CASE("Comparison") {
	CHECK(equal == (rat1 == rat3));
	CHECK(equal == (rat1 != rat2));
	CHECK((rat1 > rat3) == false);
	CHECK((rat1 < rat3) == false);
	CHECK((rat1 >= rat3) == true);
	CHECK((rat1 <= rat3) == true);
}

Rational rat4(9, 3);
Rational rat5(3, 1);

TEST_CASE("Reducing") {
	CHECK(rat4 == rat5);
}

Rational a(0);
Rational a1(0, 1);
Rational b(3, 9);
Rational b1 = b;

TEST_CASE("Ctor") {
	CHECK(a == a1);
	CHECK(b == b1);
}
*/




