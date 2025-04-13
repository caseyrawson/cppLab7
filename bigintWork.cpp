#include <iostream>
#include "./bigint.h"

using namespace std;

ostream & operator<<(ostream &os, pair<bigint, bigint> & fraction) {
    os << fraction.first
        << " / "
        << fraction.second;
        
}

pair<bigint, bigint> product(pair<bigint, bigint> fraction1, pair<bigint, bigint> fraction2) {
    bigint numerator = fraction1.first * fraction2.first;
    bigint denominator = fraction1.second * fraction2.second;

    return pair<bigint, bigint>(numerator, denominator);
}

pair<bigint, bigint> sum(pair<bigint, bigint> fraction1, pair<bigint, bigint> fraction2) {
    bigint numerator = fraction1.first * fraction2.second + fraction1.second * fraction2.first;
    bigint denominator = fraction1.second * fraction2.second;
    bigint myGcd = big_gcd(numerator, denominator);

    return pair<bigint, bigint>(numerator / myGcd, denominator / myGcd);
}

int main(int argc, char const *argv[])
{
    pair<bigint, bigint> fraction1("1", "2"), fraction2("3", "4");

    pair<bigint, bigint> newFractionProduct = product(fraction1, fraction2);
    pair<bigint, bigint> newFractionSum = sum(fraction1, fraction2);

    cout << newFractionProduct << endl;

    cout << newFractionSum << endl;

    bigint myBigInt("2");
    int myInt = 2;

    for (int i = 0; i < 15; i++) {
        myInt *= 2;
        myBigInt *= 2;

        bigint compare(myInt);

        if (compare != myBigInt) {
            cerr << "big int works, but int overflows: " << myBigInt << " where i = " << int
        }
    }

    cout << myBigInt << endl;
    cout << myInt << endl;

    return 0;
}
