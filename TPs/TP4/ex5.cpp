#include "exercises.h"

unsigned long s_recursive(unsigned int n, unsigned int k) {
    if (k == 1 || k == n) return 1;
    return s_recursive(n-1, k-1) + k * s_recursive(n-1, k);
}

unsigned long b_recursive(unsigned int n) {
    int res = 0;
    for (int k = 1; k <= n; k++) res += s_recursive(n, k);
    return res;
}

unsigned long s_dynamic(unsigned int n, unsigned int k) {
    unsigned int s[n + 1][k + 1];
    for (unsigned int i = 0; i <= n; i++) { std::fill_n(s[i], k + 1, 1); }

    for (unsigned int i = 1; i <= n; i++) {
        for (unsigned int j = 2; j <= std::min(k, i - 1); j++) {
            s[i][j] = s[i - 1][j - 1] + j * s[i - 1][j];
        }
    }

    return s[n][k];

    /* was on UC slides but this shit does not work, blame Rossetti
    int c[n-k+1];
    std::fill_n(c, n-k+1, 1);

    for (int i = 1; i <= k; i++) {
        for (int j = i; j <= n-k; j++) {
            c[j] += c[j-1];
        }
    }

    return c[n-k];*/
}

unsigned long b_dynamic(unsigned int n) {
    int res = 0;
    for (int k = 1; k <= n; k++) res += s_dynamic(n, k);
    return res;
}

/// TESTS ///
#include <gtest/gtest.h>

TEST(TP4_Ex5, testPartitioningRecursive) {
    EXPECT_EQ(1,s_recursive(3,3));
    EXPECT_EQ(3025,s_recursive(9,3));
    EXPECT_EQ(22827,s_recursive(10,6));

    EXPECT_EQ(5,b_recursive(3));
    EXPECT_EQ(203,b_recursive(6));
    EXPECT_EQ(1382958545,b_recursive(15));
}

TEST(TP4_Ex5, testPartitioningDynamic) {
    EXPECT_EQ(1,s_dynamic(3,3));
    EXPECT_EQ(3025,s_dynamic(9,3));
    EXPECT_EQ(22827,s_dynamic(10,6));

    EXPECT_EQ(5,b_dynamic(3));
    EXPECT_EQ(203,b_dynamic(6));
    EXPECT_EQ(1382958545,b_dynamic(15));
}