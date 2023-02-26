#include <rational.hpp>
#include <iostream>
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

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

TEST_CASE("Comparison") {
	CHECK(equal == (rat1 == rat3));
	CHECK(equal == (rat1 != rat2));
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



