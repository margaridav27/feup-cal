#include "exercises.h"
#include <unordered_map>

bool allowedByStock(unsigned int C[], unsigned int Stock[], int p[], unsigned int n, int i, int k) {
    std::unordered_map<int, int> mp;
    for (int i = 0; i < n; ++i) {
        mp.insert(std::make_pair(C[i], i));
    }

    unsigned int tempUsedCoins[n];
    std::fill_n(tempUsedCoins, n, 0);

    int pOldVal = p[k];
    p[k] = C[i - 1]; //using the coin

    for (int i = k; i > 0; i -= p[i]) { //filling the usedCoins temporary array
        tempUsedCoins[mp.at(p[i])]++;
    }

    for (int i = 0; i < n; i++) {
        if (tempUsedCoins[i] > Stock[i])  { //there is at least one coin of which the stock we exceeded
            p[k] = pOldVal;
            return false;
        }
    }

    p[k] = pOldVal; //restoring the value (it will be set again in the main function)
    return true;
}

bool changeMakingDP(unsigned int C[], unsigned int Stock[], unsigned int n, unsigned int T, unsigned int usedCoins[]) {
    std::fill_n(usedCoins, n, 0);

    //represents the needed amount of coins by using the coin introduced in the current iteration
    std::vector<int> c(T+1, T+1); c[0] = 0;

    //saves the last coin used to make the k amount
    int p[T+1]; p[0] = 0;

    for (int i = 1; i <= n; i++) {
        for (int k = C[i - 1]; k <= T; k++) {
            if (c[k - C[i - 1]] + 1 < c[k]) { //in this step we decide whether to use the coin or not
                if (allowedByStock(C, Stock, p, n, i, k)) { //we would benefit of using the coin, but if we do, is there enough stock?
                    c[k] = 1 + c[k - C[i - 1]];
                    p[k] = C[i - 1];
                }
            }
        }
    }

    if(c[T] > T) return false;

    std::unordered_map<int, int> mp;
    for (int i = 0; i < n; ++i) {
        mp.insert(std::make_pair(C[i], i));
    }
    for (int i = T; i > 0; i -= p[i]) {
        usedCoins[mp.at(p[i])]++;
    }

    return true;
}

/// TESTS ///
#include <gtest/gtest.h>

TEST(TP4_Ex3, hasChangeCanonical) {
    unsigned int C[] = {1,2,5,10};
    unsigned int Stock[] = {1,1,1,1};
    unsigned int n = 4;
    unsigned int usedCoins[4];

    EXPECT_EQ(changeMakingDP(C,Stock,n,13,usedCoins), true);
    EXPECT_EQ(usedCoins[0], 1);
    EXPECT_EQ(usedCoins[1], 1);
    EXPECT_EQ(usedCoins[2], 0);
    EXPECT_EQ(usedCoins[3], 1);

    unsigned int Stock2[] = {1,2,4,2};
    EXPECT_EQ(changeMakingDP(C,Stock2,n,38,usedCoins), true);
    EXPECT_EQ(usedCoins[0], 1);
    EXPECT_EQ(usedCoins[1], 1);
    EXPECT_EQ(usedCoins[2], 3);
    EXPECT_EQ(usedCoins[3], 2);

    unsigned int Stock3[] = {10,2,4,2};
    EXPECT_EQ(changeMakingDP(C,Stock3,n,10,usedCoins), true);
    EXPECT_EQ(usedCoins[0], 0);
    EXPECT_EQ(usedCoins[1], 0);
    EXPECT_EQ(usedCoins[2], 0);
    EXPECT_EQ(usedCoins[3], 1);
}

TEST(TP4_Ex3, hasChangeNonCanonical) {
    unsigned int C[] = {1,4,5};
    unsigned int Stock[] = {2,2,1};
    unsigned int n = 3;
    unsigned int usedCoins[3];

    EXPECT_EQ(changeMakingDP(C,Stock,n,6,usedCoins), true);
    EXPECT_EQ(usedCoins[0], 1);
    EXPECT_EQ(usedCoins[1], 0);
    EXPECT_EQ(usedCoins[2], 1);

    EXPECT_EQ(changeMakingDP(C,Stock,n,8,usedCoins), true);
    EXPECT_EQ(usedCoins[0], 0);
    EXPECT_EQ(usedCoins[1], 2);
    EXPECT_EQ(usedCoins[2], 0);

    unsigned int Stock2[] = {8,2,1};
    EXPECT_EQ(changeMakingDP(C,Stock2,n,7,usedCoins), true);
    EXPECT_EQ(usedCoins[0], 2);
    EXPECT_EQ(usedCoins[1], 0);
    EXPECT_EQ(usedCoins[2], 1);

    EXPECT_EQ(changeMakingDP(C,Stock2,n,8,usedCoins), true);
    EXPECT_EQ(usedCoins[0], 0);
    EXPECT_EQ(usedCoins[1], 2);
    EXPECT_EQ(usedCoins[2], 0);
}

TEST(TP4_Ex3, hasNoChange) {
    unsigned int C[] = {1,2,5,10};
    unsigned int Stock[] = {0,1,1,1};
    unsigned int n = 4;
    unsigned int usedCoins[4];

    EXPECT_EQ(changeMakingDP(C,Stock,n,18,usedCoins), false);
    EXPECT_EQ(changeMakingDP(C,Stock,n,1,usedCoins), false);
}