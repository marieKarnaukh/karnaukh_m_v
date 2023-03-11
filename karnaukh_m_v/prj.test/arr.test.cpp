#include <iostream>
#include <arrayd/arrayd.hpp>
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>

TEST_CASE("123") {
    ArrayD a(3);
    for (int i = 0; i < a.size(); ++i) {
        a[i] = i;
    }
    for (int i = 0; i < 3; ++i) {
        CHECK(a[i] == i);
    }
}