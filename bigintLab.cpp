#include "./bigint.h"
#include <iostream>
#include <chrono>
#include <utility>
#include <string>
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "include/doctest.h"

using namespace std;

ostream & operator<<(ostream &os, const pair<bigint, bigint> &fraction) {
    os << fraction.first << " / " << fraction.second;
    return os;
}

pair<bigint, bigint> product(const pair<bigint, bigint>& fraction1, 
    const pair<bigint, bigint>& fraction2) {
        // Cast to non-const so that * works
        bigint a = fraction1.first; 
        bigint b = fraction2.first; 
        bigint numerator = a * b;

        bigint c = fraction1.second;
        bigint d = fraction2.second;
        bigint denominator = c * d;

        return pair<bigint, bigint>(numerator, denominator);
    }


pair<bigint, bigint> sum(const pair<bigint, bigint> &fraction1, 
    const pair<bigint, bigint> &fraction2) {
        // Create non-const copies so * works
        bigint a = fraction1.first;
        bigint b = fraction1.second;
        bigint c = fraction2.first;
        bigint d = fraction2.second;

        bigint numerator = a * d + b * c;
        bigint denominator = b * d;

        bigint myGcd = big_gcd(numerator, denominator);
        return pair<bigint, bigint>(numerator / myGcd, denominator / myGcd);
    }


// Test sum function
TEST_CASE("Test fraction sum") {
    pair<bigint, bigint> fraction1("1", "2");
    pair<bigint, bigint> fraction2("3", "4");
    auto result = sum(fraction1, fraction2);
    // Expected 1/2 + 3/4 = 5/4
    pair<bigint, bigint> expected("5", "4");
    CHECK(result.first == expected.first);
    CHECK(result.second == expected.second);
}

// Test product function
TEST_CASE("Test fraction product") {
    pair<bigint, bigint> fraction1("1", "2");
    pair<bigint, bigint> fraction2("3", "4");
    auto result = product(fraction1, fraction2);
    // Expected 1/2 * 3/4 = 3/8
    pair<bigint, bigint> expected("3", "8");
    CHECK(result.first == expected.first);
    CHECK(result.second == expected.second);
}

// Test overflow for ints
TEST_CASE("Test int overflow vs bigint") {
    int myInt = 2;
    bigint myBigInt("2");
    bool overflowOccurred = false;

    for (int i = 0; i < 30; i++) {
        myInt *= 2;
        myBigInt *= 2;

        bigint compare(myInt);
        if (compare != myBigInt) {
            overflowOccurred = true;
            cout << "bigint works, but int overflows at " << myBigInt 
                << " where i = " << i << endl;
            break;
        }
    }
    CHECK(overflowOccurred == true);
}

// Timing comparisons for multiplication
TEST_CASE("Timing comparisons for int, long, and bigint") {
    using namespace chrono;
    const int iterations = 5000;

    auto start = high_resolution_clock::now();
    int myInt = 2;
    for (int i = 0; i < iterations; i++) {
        myInt *= 2;
    }
    auto end = high_resolution_clock::now();
    auto intDuration = duration_cast<microseconds>(end - start).count();

    start = high_resolution_clock::now();
    long myLong = 2;
    for (int i = 0; i < iterations; i++) {
        myLong *= 2;
    }
    end = high_resolution_clock::now();
    auto longDuration = duration_cast<microseconds>(end - start).count();

    start = high_resolution_clock::now();
    bigint myBigInt("2");
    for (int i = 0; i < iterations; i++) {
        myBigInt *= 2;
    }
    end = high_resolution_clock::now();
    auto bigIntDuration = duration_cast<microseconds>(end - start).count();

    // Output the timings
    cout << "\nTiming comparison (" << iterations << " multiplications):\n";
    cout << "int:    " << intDuration   << " microseconds\n";
    cout << "long:   " << longDuration  << " microseconds\n";
    cout << "bigint: " << bigIntDuration << " microseconds\n";

    CHECK(true);
}
