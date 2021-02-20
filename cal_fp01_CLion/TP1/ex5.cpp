// By: Gonçalo Leão

#include "exercises.h"

unsigned int sumArray(unsigned int a[], unsigned int n) {
    unsigned int sum = 0;
    for(unsigned int i = 0; i < n; i++) {
        sum += a[i];
    }
    return sum;
}

#include <iostream>

bool isCanonical(unsigned int C[], unsigned int n) {
    if (n < 4) return true;

    unsigned int greedy[n]; std::fill_n(greedy, n, 0);
    unsigned int brute[n]; std::fill_n(brute, n, 0);
    unsigned int stock[n]; std::fill_n(stock, n, 100); //simulating an unlimited stock

    for (int i = C[2] + 1; i < C[n - 2] + C[n - 1]; i++) {
        //if the greedy algorithm is not able to find the minimum amount of coins summing up i, obviously the greedy algorithm won't be able to do it either
        if (!changeMakingBF(C, stock, n, i, brute)) return false;

        //if the greedy algorithm is not able to find the minimum amount of coins summing up i, C is said to be non-canonical
        if (!changeMakingGreedy(C, stock, n, i, greedy)) return false;

        //if a counter-example is found via brute force, that will also make C to be non-canonical
        if (sumArray(brute, n) < sumArray(greedy, n)) return false;
    }

    return true;
}


/// TESTS ///
#include <gtest/gtest.h>

TEST(TP1_Ex5, canonicalTrue) {
    unsigned int C[] = {1,2,5};
    EXPECT_EQ(isCanonical(C,3), true);

    unsigned int C2[] = {1,2,5,10};
    EXPECT_EQ(isCanonical(C2,4), true);
}

TEST(TP1_Ex5, canonicalFalse) {
    unsigned int C[] = {1,4,5};
    EXPECT_EQ(isCanonical(C,3), true);
}